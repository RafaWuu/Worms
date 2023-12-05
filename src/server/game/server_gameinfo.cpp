//
// Created by xguss on 01/11/23.
//
#include "server_gameinfo.h"

#include <vector>

#include "server_game.h"

GameInfo::GameInfo(const Game& game): scenario(game.name) {
    id = game.game_id;
    players = game.id_lists.size();
    max_players = game.max_players;
    status = game.had_started;
}

void GameInfo::serialize(BaseProtocol& bp) {
    bp.send_2byte_number(id);
    bp.send_2byte_number(scenario.length());

    std::vector<char> buffer(scenario.c_str(), scenario.c_str() + scenario.length());
    bp.send_char_vector(buffer);

    bp.send_1byte_number(players);
    bp.send_1byte_number(max_players);
    bp.send_1byte_number(status);
}

GameInfo::GameInfo(size_t id, const std::string& scenario, uint8_t players, uint8_t max_players,
                   bool status) {
    this->id = id;
    this->scenario = scenario;
    this->players = players;
    this->max_players = max_players;
    this->status = status;
}
