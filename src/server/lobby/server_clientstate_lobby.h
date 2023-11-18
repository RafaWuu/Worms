//
// Created by xguss on 31/10/23.
//

#ifndef WORMS_SERVER_CLIENTSTATE_LOBBY_H
#define WORMS_SERVER_CLIENTSTATE_LOBBY_H

#include <memory>

#include "../server_clientstate.h"
#include "../server_protocol.h"

#include "server_lobby.h"

class LobbyClientState: public ClientState {
private:
    LobbyMonitor& lobby;
    std::shared_ptr<Game> game;

public:
    LobbyClientState(uint16_t id, LobbyMonitor& lobby, ServerProtocol& gameProtocol);
    LobbyClientState(const LobbyClientState&) = delete;
    LobbyClientState& operator=(const LobbyClientState&) = delete;

    std::unique_ptr<ClientState> run() override;
    void kill() override;
    bool is_dead() override;

    ~LobbyClientState() override = default;
};

#endif  // WORMS_SERVER_CLIENTSTATE_LOBBY_H
