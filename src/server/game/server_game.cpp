//
// Created by xguss on 31/10/23.
//

#include "server_game.h"

#include <memory>
#include <string>
#include <utility>

#include <bits/stdc++.h>

#include "../../common/common_socket.h"

#include "server_statusbroadcast_monitor.h"

Game::Game(uint16_t game_id, std::string& scenario, uint16_t owner_id_):
        game_world(scenario),
        game_id(game_id),
        owner_id(owner_id_),
        id_lists(),
        event_queue(),
        broadcastMonitor(),
        eventHandler(game_world, broadcastMonitor, id_lists, had_started, owner_id),
        is_alive(true),
        had_started(false),
        name(scenario) {
    id_lists.push_back(owner_id);

    this->start();
}

void Game::run() {
    while (is_alive) {
        try {
            std::shared_ptr<GameEvent> event;
            bool queue_is_empty = !event_queue.try_pop(event);

            while (!queue_is_empty) {
                event->execute(this->eventHandler);
                queue_is_empty = !event_queue.try_pop(event);
            }

            if (had_started) {
                game_world.update_worms();
                game_world.step(120);

                broadcastMonitor.send_status_toall(
                        std::make_shared<GameStatusRunning>(0, game_world));
            }

        } catch (ClosedSocket& e) {
            is_alive = false;
        }
    }
}

void Game::kill() { is_alive = false; }

bool Game::is_dead() { return !is_alive; }

void Game::push_event(const std::shared_ptr<GameEvent>& event) { event_queue.push(event); }

void Game::subscribe_queue(Queue<std::shared_ptr<GameStatus>>& queue, uint16_t client_id) {
    broadcastMonitor.add_queue(queue, client_id);
    broadcastMonitor.send_status(client_id, std::make_shared<GameStatusScenario>(game_world));
}

void Game::add_player(uint16_t client_id) {
    std::lock_guard<std::mutex> lock(mutex);

    id_lists.push_back(client_id);
}

void Game::exit_game(uint16_t client_id) {
    broadcastMonitor.remove_queue(client_id);

    std::lock_guard<std::mutex> lock(mutex);

    auto it = std::find(id_lists.begin(), id_lists.end(), client_id);

    if (it != id_lists.end()) {
        id_lists.erase(it);
    }

    if (owner_id == client_id)
        owner_id = id_lists[0];
}

GameInfo Game::get_info() { return GameInfo(this->game_id, this->name); }
