//
// Created by xguss on 31/10/23.
//

#include "server_clientstate_game.h"

#include <memory>
#include <utility>

#include "server_game.h"

GameClientState::GameClientState(uint16_t client_id, ServerProtocol& gameProtocol, Game& game):
        game(game),
        outgoing_q(),
        sender(outgoing_q, gameProtocol),
        ClientState(client_id, gameProtocol) {

    game.subscribe_queue(outgoing_q, client_id);
    sender.start();
}

std::unique_ptr<ClientState> GameClientState::run() {
    while (is_alive) {
        try {
            std::unique_ptr<GameEvent> event = gp.recv_game_msg(this->client_id);
            if (!event) {
                is_alive = false;
            }
            game.push_event(std::move(event));
        } catch (InvalidMsg& e) {
            std::cerr << e.what() << std::endl;
        } catch (ClosedSocket& e) {
            is_alive = false;
        } catch (ClosedQueue& e) {
            if (is_alive) {
                is_alive = false;
                std::cerr << e.what() << std::endl;
            }
        }
    }

    return nullptr;
}

bool GameClientState::is_dead() { return !is_alive || sender.is_dead(); }

void GameClientState::kill() { this->is_alive = false; }

GameClientState::~GameClientState() {
    sender.kill();
    game.exit_game(client_id);
    sender.join();
}
