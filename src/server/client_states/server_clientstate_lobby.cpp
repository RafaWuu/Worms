//
// Created by xguss on 31/10/23.
//

#include "server_clientstate_lobby.h"

#include "../server_clienthandler.h"
#include "../server_lobby_request.h"
#include "../server_protocol.h"

#include "memory"
#include "server_clientstate_game.h"

LobbyClientState::LobbyClientState(Lobby& lobby, ServerProtocol& gameProtocol):
        lobby(lobby), gp(gameProtocol), game(nullptr) {}

std::unique_ptr<ClientState> LobbyClientState::run() {
    while (is_alive) {
        try {
            std::unique_ptr<LobbyRequest> request = gp.recv_lobby_msg();
            game = request->execute(lobby, gp);

            if (game != nullptr) {
                return std::make_unique<GameClientState>(gp, *game);
            }
        } catch (InvalidMsg& e) {
        } catch (ClosedSocket& e) {
            is_alive = false;
        }
    }

    return nullptr;
}

void LobbyClientState::kill() { is_alive = false; }

bool LobbyClientState::is_dead() { return !is_alive; }
