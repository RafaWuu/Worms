//
// Created by xguss on 16/11/23.
//

#ifndef WORMS_GAMEINFO_H
#define WORMS_GAMEINFO_H

#include <cstdint>
#include <string>

class GameInfo {
private:
    bool status;
    uint8_t max_players;
    uint8_t players;
    std::string name;
    uint16_t id;

public:
    friend class GameInfoView;
    GameInfo(uint16_t id, std::string& name, uint8_t players, uint8_t max_players, bool status);
};
#endif  // WORMS_GAMEINFO_H
