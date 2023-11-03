//
// Created by xguss on 01/11/23.
//

#ifndef WORMS_SERVER_LOBBY_REQUEST_H
#define WORMS_SERVER_LOBBY_REQUEST_H

#include <memory>
#include <string>

#include "../server_protocol.h"

#include "server_lobby.h"

class LobbyRequest {
public:
    LobbyRequest() = default;
    virtual std::shared_ptr<Game> execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                          uint16_t client_id) = 0;
};

class LobbyRequestNewGame: public LobbyRequest {
private:
    std::string scenario;

public:
    explicit LobbyRequestNewGame(const std::string& s);
    std::shared_ptr<Game> execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                  uint16_t client_id) override;
};

class LobbyRequestJoinGame: public LobbyRequest {
private:
    uint16_t id;

public:
    explicit LobbyRequestJoinGame(uint16_t id);
    std::shared_ptr<Game> execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                  uint16_t client_id) override;
};


class LobbyRequestListGames: public LobbyRequest {
private:
public:
    LobbyRequestListGames() = default;

    std::shared_ptr<Game> execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                  uint16_t client_id) override;
};


#endif  // WORMS_SERVER_LOBBY_REQUEST_H
