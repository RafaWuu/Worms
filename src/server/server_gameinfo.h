//
// Created by xguss on 01/11/23.
//

#ifndef WORMS_SERVER_GAMEINFO_H
#define WORMS_SERVER_GAMEINFO_H

#include <string>

class GameInfo {
public:
    GameInfo(size_t id, const std::string& scenario);
    size_t id;
    std::string scenario;
};
#endif  // WORMS_SERVER_GAMEINFO_H
