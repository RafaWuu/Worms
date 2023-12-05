//
// Created by xguss on 01/11/23.
//

#ifndef WORMS_SERVER_GAMEINFO_H
#define WORMS_SERVER_GAMEINFO_H

#include <string>

#include "common_baseprotocol.h"

class Game;

class GameInfo {
private:
    size_t id;
    std::string scenario;
    uint8_t players;
    uint8_t max_players;
    bool status;

public:
    explicit GameInfo(const Game& game);
    GameInfo(size_t id, const std::string& scenario, uint8_t players, uint8_t max_players,
             bool status);

    void serialize(BaseProtocol& bp);
};
#endif  // WORMS_SERVER_GAMEINFO_H
