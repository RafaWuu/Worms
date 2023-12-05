

#include "server_clientstate_lobby.h"

#include "../game/server_clientstate_game.h"
#include "../server_client.h"
#include "../server_protocol.h"

#include "memory"
#include "server_error.h"
#include "server_lobby_request.h"
#include "server_lobby_response.h"

LobbyClientState::LobbyClientState(uint16_t id, LobbyMonitor& lobby, ServerProtocol& gameProtocol):
        lobby(lobby), ClientState(id, gameProtocol) {
    gp.send_lobby_newclient(client_id);
}

std::unique_ptr<ClientState> LobbyClientState::run() {
    while (is_alive) {
        try {
            std::unique_ptr<LobbyRequest> request = gp.recv_lobby_msg();
            std::shared_ptr<Game> game = request->execute(lobby, gp, client_id);

            if (game != nullptr) {
                return std::make_unique<GameClientState>(client_id, gp, *game);
            }
        } catch (InvalidMsg& e) {
            std::cerr << e.what() << std::endl;
            e.send(gp);
        } catch (LobbyError& e) {
            std::cerr << e.what() << std::endl;
            e.send(gp);
        } catch (ClosedSocket& e) {
            std::cerr << e.what() << std::endl;
            is_alive = false;
        } catch (YAML::Exception& e) {
            std::cerr << e.what() << std::endl;
            LobbyError lb(0, "Error loading scenario", 0);
            lb.send(gp);
        }
    }

    return nullptr;
}

void LobbyClientState::kill() { is_alive = false; }

bool LobbyClientState::is_dead() { return !is_alive; }
