//
// Created by xguss on 31/10/23.
//

#ifndef WORMS_SERVER_CLIENTSTATE_LOBBY_H
#define WORMS_SERVER_CLIENTSTATE_LOBBY_H

#include <memory>

#include "../server_lobby.h"
#include "../server_protocol.h"

#include "server_clientstate.h"

class LobbyClientState: public ClientState {
private:
    Lobby& lobby;
    ServerProtocol& gp;
    std::unique_ptr<Game> game;

public:
    LobbyClientState(Lobby& lobby, ServerProtocol& gameProtocol);
    std::unique_ptr<ClientState> run() override;
    void kill() override;
    bool is_dead() override;

    ~LobbyClientState() override = default;
};

#endif  // WORMS_SERVER_CLIENTSTATE_LOBBY_H
