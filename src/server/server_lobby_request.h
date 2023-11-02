//
// Created by xguss on 01/11/23.
//

#ifndef WORMS_SERVER_LOBBY_REQUEST_H
#define WORMS_SERVER_LOBBY_REQUEST_H

#include <memory>
#include <string>

#include "server_lobby.h"
#include "server_protocol.h"

class ServerProtocol;

class LobbyRequest {
public:
    LobbyRequest() = default;
    virtual std::unique_ptr<Game> execute(Lobby& lobby, ServerProtocol& gp) = 0;
};

class LobbyRequestNewGame: public LobbyRequest {
private:
    std::string scenario;

public:
    explicit LobbyRequestNewGame(const std::string& s);
    std::unique_ptr<Game> execute(Lobby& lobby, ServerProtocol& gp) override;
};

class LobbyRequestJoinGame: public LobbyRequest {
private:
    size_t id;

public:
    explicit LobbyRequestJoinGame(size_t id);
    std::unique_ptr<Game> execute(Lobby& lobby, ServerProtocol& gp) override;
};


class LobbyRequestListGames: public LobbyRequest {
private:
public:
    LobbyRequestListGames() = default;

    std::unique_ptr<Game> execute(Lobby& lobby, ServerProtocol& gp) override;
};


#endif  // WORMS_SERVER_LOBBY_REQUEST_H
