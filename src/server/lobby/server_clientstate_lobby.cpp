//
// Created by xguss on 31/10/23.
//

#include "server_clientstate_lobby.h"

#include "../game/server_clientstate_game.h"
#include "../server_client.h"
#include "../server_protocol.h"

#include "memory"
#include "server_error.h"
#include "server_lobby_answer.h"
#include "server_lobby_request.h"

LobbyClientState::LobbyClientState(uint16_t id, LobbyMonitor& lobby, ServerProtocol& gameProtocol):
        lobby(lobby), game(nullptr), ClientState(id, gameProtocol) {}

std::unique_ptr<ClientState> LobbyClientState::run() {
    while (is_alive) {
        try {
            gp.send_lobby_newclient(client_id);
            std::unique_ptr<LobbyRequest> request = gp.recv_lobby_msg();
            game = request->execute(lobby, gp, client_id);

            if (game != nullptr) {
                return std::make_unique<GameClientState>(client_id, gp, *game);
            }
        } catch (InvalidMsg& e) {
            std::cerr << e.what() << std::endl;
        } catch (LobbyError& e) {
            std::cerr << e.what() << std::endl;
            e.send(gp);
        } catch (ClosedSocket& e) {
            is_alive = false;
        }
    }

    return nullptr;
}

void LobbyClientState::kill() { is_alive = false; }

bool LobbyClientState::is_dead() { return !is_alive; }
