#include "server_lobby.h"

#include <algorithm>
#include <string>

#include "server_gameinfo.h"

//
// Created by xguss on 31/10/23.
//
Lobby::Lobby(): id(1) {}

size_t Lobby::create_game(std::string scenario) {
    games_map.emplace(id, scenario);
    this->id++;
    return id - 1;
}

std::unique_ptr<Game> Lobby::join_game(size_t game_id) {
    auto it = games_map.find(game_id);
    if (it == games_map.end())
        throw InvalidGameID();

    it->second.player_count++;

    return std::make_unique<Game>(it->second);
}

std::vector<GameInfo> Lobby::list_games() {
    std::vector<GameInfo> v;

    std::transform(games_map.begin(), games_map.end(), v.begin(),
                   [](const auto& g) { return GameInfo(g.first, g.second.name); });

    return v;
}
