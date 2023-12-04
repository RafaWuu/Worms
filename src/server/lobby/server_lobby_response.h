//
// Created by xguss on 01/11/23.
//

#ifndef WORMS_SERVER_LOBBY_RESPONSE_H
#define WORMS_SERVER_LOBBY_RESPONSE_H

#include <vector>

#include "../game/server_gameinfo.h"
#include "../server_protocol.h"

class LobbyResponse {
public:
    LobbyResponse() = default;
    LobbyResponse(const LobbyResponse&) = delete;
    LobbyResponse& operator=(const LobbyResponse&) = delete;

    virtual void send(ServerProtocol& gp) = 0;
};

class LobbyResponseError: LobbyResponse {
private:
    uint8_t code;

public:
    explicit LobbyResponseError(uint8_t code);
    void send(ServerProtocol& gp) override;
};

class LobbyResponseGame: LobbyResponse {
private:
    uint16_t id;

public:
    explicit LobbyResponseGame(uint16_t id);
    void send(ServerProtocol& gp) override;
};


class LobbyResponseGamesList: LobbyResponse {
private:
    std::vector<GameInfo>& games;

public:
    explicit LobbyResponseGamesList(std::vector<GameInfo>& games);

    void send(ServerProtocol& gp) override;
};

class LobbyResponseScenariosList: LobbyResponse {
private:
    std::map<std::string, uint16_t>& scenarios;

public:
    explicit LobbyResponseScenariosList(std::map<std::string, uint16_t>& scenarios);

    void send(ServerProtocol& gp) override;
};

#endif  // WORMS_SERVER_LOBBY_RESPONSE_H
