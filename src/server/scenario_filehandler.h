

#ifndef WORMS_SCENARIO_FILEHANDLER_H
#define WORMS_SCENARIO_FILEHANDLER_H

#include <cstdint>
#include <map>
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

    std::map<std::string, uint16_t> get_info();

    void get_scenario(GameWorld& game, const std::string& name);
};
#endif  // WORMS_SCENARIO_FILEHANDLER_H
