//
// Created by xguss on 31/10/23.
//

#ifndef WORMS_SERVER_LOBBY_H
#define WORMS_SERVER_LOBBY_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "server_game.h"
#include "server_gameinfo.h"

struct InvalidGameID: public std::runtime_error {
    InvalidGameID(): std::runtime_error("The requested game with specified id was not found") {}
};

class Lobby {
private:
    std::map<uint8_t, Game> games_map;
    size_t id;

public:
    Lobby();
    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

    size_t create_game(std::string name);
    std::unique_ptr<Game> join_game(size_t game_id);

    std::vector<GameInfo> list_games();
};

#endif  // WORMS_SERVER_LOBBY_H
