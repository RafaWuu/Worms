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
    virtual ~LobbyRequest() = default;
    LobbyRequest(const LobbyRequest&) = delete;
    LobbyRequest& operator=(const LobbyRequest&) = delete;

    virtual std::shared_ptr<Game> execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                          uint16_t client_id) = 0;
};

class LobbyRequestNewGame: public LobbyRequest {

public:
    explicit LobbyRequestNewGame(const std::string&& s);
    ~LobbyRequestNewGame() override = default;

    std::shared_ptr<Game> execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                  uint16_t client_id) override;

    std::string scenario;
};

class LobbyRequestJoinGame: public LobbyRequest {
private:
    uint16_t id;

public:
    explicit LobbyRequestJoinGame(uint16_t id);
    ~LobbyRequestJoinGame() override = default;

    std::shared_ptr<Game> execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                  uint16_t client_id) override;
};


class LobbyRequestListGames: public LobbyRequest {
private:
public:
    LobbyRequestListGames() = default;
    ~LobbyRequestListGames() override = default;

    std::shared_ptr<Game> execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                  uint16_t client_id) override;
};


#endif  // WORMS_SERVER_LOBBY_REQUEST_H
