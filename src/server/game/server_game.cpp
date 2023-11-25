//
// Created by xguss on 31/10/23.
//

#include "server_game.h"

#include <memory>
#include <string>
#include <utility>

#include <bits/stdc++.h>

#include "../../common/common_socket.h"
#include "../configuration/configuration.h"

#include "server_error.h"
#include "server_statusbroadcast_monitor.h"

Game::Game(uint16_t game_id, const std::string& scenario, uint16_t owner_id_,
           Queue<uint16_t>& reap_queue):
        game_world(scenario),
        game_id(game_id),
        owner_id(owner_id_),
        id_lists(),
        event_queue(),
        broadcastMonitor(),
        eventHandler(game_world, broadcastMonitor, id_lists, had_started, owner_id),
        reaper_queue(reap_queue),
        is_alive(true),
        had_started(false),
        name(scenario) {

    this->start();
}

void Game::run() {
    // el servidor no deberia estar necesariamente sincronizado con el cliente
    // ademas hay un tema de semantica que no esta bueno
    // frames refiere a imagenes, en el server nos referimos a "tick" (tickrate, genericamente)
    auto rate = 1.0 / Configuration::get_instance().get_fps();

    while (is_alive) {
        try {
            auto start = std::chrono::high_resolution_clock::now();


            std::shared_ptr<GameEvent> event;
            size_t n_events = event_queue.get_size();

            for (size_t i = 0; i < n_events; ++i) {
                bool queue_is_empty = !event_queue.try_pop(event);

                if (!queue_is_empty) {
                    event->execute(this->eventHandler);
                }
            }

            if (had_started) {
                game_world.update_entities();
                game_world.step(1);

                broadcastMonitor.send_status_toall(
                        std::make_shared<GameStatusRunning>(0, game_world));
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed =
                    std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

            auto rest = rate - elapsed;
            if (rest < 0) {
                auto behind = -rest;
                auto lost = behind - fmod(behind, rate);
                start += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(
                        std::chrono::duration<double>(lost));
            } else {
                std::this_thread::sleep_for(std::chrono::duration<double>(rest));
            }

            start += std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(
                    std::chrono::duration<double>(rate));

        } catch (GameError& e) {
            std::cerr << e.what() << std::endl;
            broadcastMonitor.send_status(e.client_id,
                                         std::make_shared<GameStatusError>(e.code, game_world));
        } catch (ClosedSocket& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}

void Game::kill() {
    is_alive = false;
    reaper_queue.push(game_id);
}

bool Game::is_dead() { return !is_alive; }

void Game::push_event(const std::shared_ptr<GameEvent>& event) { event_queue.push(event); }

void Game::subscribe_queue(Queue<std::shared_ptr<GameStatus>>& queue, uint16_t client_id) {
    broadcastMonitor.add_queue(queue, client_id);
    broadcastMonitor.send_status(client_id, std::make_shared<GameStatusScenario>(game_world));
}

void Game::add_player(uint16_t client_id) {
    std::lock_guard<std::mutex> lock(mutex);

    auto it = std::find(id_lists.begin(), id_lists.end(), client_id);

    if (it != id_lists.end())
        throw ClientAlreadyInGameLobbyError(client_id, game_id);

    id_lists.push_back(client_id);
}

void Game::exit_game(uint16_t client_id) {
    broadcastMonitor.remove_queue(client_id);

    std::lock_guard<std::mutex> lock(mutex);

    auto it = std::find(id_lists.begin(), id_lists.end(), client_id);

    if (it != id_lists.end()) {
        id_lists.erase(it);
    }

    if (id_lists.empty()) {
        kill();
        return;
    }

    if (owner_id == client_id)
        owner_id = id_lists[0];
}

GameInfo Game::get_info() const { return GameInfo(*this); }
