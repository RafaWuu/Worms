#include "server_lobby.h"

#include <algorithm>
#include <string>

#include "../game/server_gameinfo.h"

#include "server_error.h"

//
// Created by xguss on 31/10/23.
//
LobbyMonitor::LobbyMonitor(): id(1) {}

uint16_t LobbyMonitor::create_game(std::string scenario, uint16_t client_id) {
    std::lock_guard<std::mutex> lock(mutex);
    games_map.emplace(id, std::make_shared<Game>(id, scenario, client_id));
    this->id++;

    return id - 1;
}

std::shared_ptr<Game> LobbyMonitor::join_game(uint16_t client_id, uint16_t game_id) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = games_map.find(game_id);
    if (it == games_map.end())
        throw InvalidGameIDLobbyError(game_id);

    it->second->add_player(client_id);

    return it->second;
}

std::vector<GameInfo> LobbyMonitor::list_games() {
    std::vector<GameInfo> v;

    std::transform(games_map.begin(), games_map.end(), v.begin(),
                   [](const auto& g) { return g.second.get()->get_info(); });

    return v;
}
