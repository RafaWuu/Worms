#ifndef LOBBY_STATE_H
#define LOBBY_STATE_H

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "gameinfo.h"

class LobbyState {
public:
    LobbyState();
    int id;
    int valid;
    std::vector<GameInfo> game_list;
    std::map<std::string, uint8_t> scenarios_map;
};
#endif
