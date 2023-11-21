//
// Created by xguss on 21/11/23.
//

#ifndef WORMS_SCENARIO_FILEHANDLER_H
#define WORMS_SCENARIO_FILEHANDLER_H

#include <cstdint>
#include <string>
#include <vector>

#include "yaml-cpp/yaml.h"

class GameWorld;

class ScenarioFileHandler {
private:
    YAML::Node config;

public:
    ScenarioFileHandler();

    bool scenario_exists(const std::string& name);

    std::vector<std::string> get_names();

    void get_scenario(GameWorld& game, const std::string& name);
};
#endif  // WORMS_SCENARIO_FILEHANDLER_H
