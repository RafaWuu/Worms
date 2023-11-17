#ifndef LOBBY_STATE_H
#define LOBBY_STATE_H

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
};
#endif
