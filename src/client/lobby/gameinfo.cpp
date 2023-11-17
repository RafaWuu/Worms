//
// Created by xguss on 16/11/23.
//

#include "gameinfo.h"

GameInfo::GameInfo(uint16_t id, std::string& name, uint8_t players, uint8_t max_players,
                   bool status):
        id(id), name(name), players(players), max_players(max_players), status(status) {}
