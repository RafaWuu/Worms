//
// Created by xguss on 31/10/23.
//

#ifndef WORMS_SERVER_GAME_H
#define WORMS_SERVER_GAME_H

#include <stdexcept>
#include <string>

struct InvalidScenarioName: public std::runtime_error {
    InvalidScenarioName(): std::runtime_error("The scenario with specified name was not found") {}
};

class Game {
private:
public:
    explicit Game(std::string& name);
    std::string name;

    int player_count;
};
#endif  // WORMS_SERVER_GAME_H
