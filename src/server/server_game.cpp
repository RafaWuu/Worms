//
// Created by xguss on 31/10/23.
//

#include "server_game.h"

#include <utility>

Game::Game(std::string& name): name(std::move(name)), player_count(0) {}
