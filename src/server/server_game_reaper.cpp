//
// Created by xguss on 17/11/23.
//

#include "server_game_reaper.h"

#include "server_error.h"

GameReaper::GameReaper(LobbyMonitor& lobby, Queue<uint16_t>& reap_queue):
        lobby(lobby), reap_queue(reap_queue), is_alive(true) {}

GameReaper::~GameReaper() { kill_all(); }

void GameReaper::run() {
    while (is_alive) {
        try {
            auto game_id = reap_queue.pop();
            lobby.close_game(game_id);

        } catch (ClosedQueue& e) {
            is_alive = false;
        } catch (InvalidGameIDLobbyError& e) {
            std::cerr << "Error al joinear partida terminada: " << e.what() << '\n';
        }
    }
}


void GameReaper::kill_all() { lobby.close_all(); }

void GameReaper::kill() { is_alive = false; reap_queue.close(); }
