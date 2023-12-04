#include "server_lobby.h"

#include <algorithm>
#include <string>

#include "../game/server_gameinfo.h"

#include "server_error.h"

//
// Created by xguss on 31/10/23.
//
LobbyMonitor::LobbyMonitor(Queue<uint16_t>& reap_queue):
        reap_queue(reap_queue), scenario_file_handler(), id(1) {}

uint16_t LobbyMonitor::create_game(const std::string& scenario, uint16_t client_id) {
    std::lock_guard<std::mutex> lock(mutex);
    games_map.emplace(id, std::make_shared<Game>(id, scenario, client_id, reap_queue));
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

std::vector<GameInfo> LobbyMonitor::list_games() const {
    std::vector<GameInfo> v;
    v.reserve(games_map.size());

    for (auto& game: games_map) {
        //  cppcheck-suppress useStlAlgorithm
        v.emplace_back(game.second->get_info());
    }

    return v;
}

std::map<std::string, uint16_t> LobbyMonitor::list_scenarios() {
    return scenario_file_handler.get_info();
}

void LobbyMonitor::close_game(uint16_t id) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = games_map.find(id);
    if (it == games_map.end())
        throw InvalidGameIDLobbyError(id);

    it->second->join();
    games_map.erase(it);
}

void LobbyMonitor::close_all() {
    std::lock_guard<std::mutex> lock(mutex);
    for (auto& game: games_map) {
        game.second->kill();
        game.second->join();
    }
}
