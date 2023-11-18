//
// Created by xguss on 01/11/23.
//

#ifndef WORMS_SERVER_LOBBY_ANSWER_H
#define WORMS_SERVER_LOBBY_ANSWER_H

#include <vector>

#include "../game/server_gameinfo.h"
#include "../server_protocol.h"

class LobbyAnswer {
public:
    LobbyAnswer() = default;
    LobbyAnswer(const LobbyAnswer&) = delete;
    LobbyAnswer& operator=(const LobbyAnswer&) = delete;

    virtual void send(ServerProtocol& gp) = 0;
};

class LobbyAnswerError: LobbyAnswer {
private:
    uint8_t code;

public:
    explicit LobbyAnswerError(uint8_t code);
    void send(ServerProtocol& gp) override;
};

class LobbyAnswerGame: LobbyAnswer {
private:
    uint16_t id;

public:
    explicit LobbyAnswerGame(uint16_t id);
    void send(ServerProtocol& gp) override;
};


class LobbyAnswerGamesList: LobbyAnswer {
private:
    std::vector<GameInfo>& games;

public:
    explicit LobbyAnswerGamesList(std::vector<GameInfo>& games);

    void send(ServerProtocol& gp) override;
};
#endif  // WORMS_SERVER_LOBBY_ANSWER_H
