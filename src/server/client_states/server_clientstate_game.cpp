//
// Created by xguss on 31/10/23.
//

#include "server_clientstate_game.h"

#include <memory>

#include "../server_game.h"

#include "server_clientstate.h"

GameClientState::GameClientState(ServerProtocol& gameProtocol, Game& game):
        outgoing_q(), gp(gameProtocol), sender(outgoing_q, gameProtocol), ClientState() {}

std::unique_ptr<ClientState> GameClientState::run() {
    sender.start();

    while (is_alive) {
        try {
            uint8_t msg = gp.recv_msg();
            outgoing_q.push(msg);
        } catch (ClosedSocket& e) {
            is_alive = false;
        } catch (ClosedQueue& e) {
            if (is_alive) {
                // Inesperado, dejo que run_expecting loggee,
                // podria ser que el broadcaste cerro mi queue por lenta
                is_alive = false;
                throw(e);
            }
        }
    }

    return nullptr;
}

bool GameClientState::is_dead() { return !is_alive || sender.is_dead(); }

void GameClientState::kill() { this->is_alive = false; }

GameClientState::~GameClientState() {
    sender.kill();
    sender.join();
}
