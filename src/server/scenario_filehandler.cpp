//
// Created by xguss on 21/11/23.
//

#include "scenario_filehandler.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "game/world/server_gameworld.h"


ScenarioFileHandler::ScenarioFileHandler() {
    try {
        config = YAML::LoadFile("../scenarios/scenarios.yaml");

    } catch (const YAML::Exception& e) {
        std::cerr << "Error yaml: " << e.what() << std::endl;
        throw(e);
    }
}

bool ScenarioFileHandler::scenario_exists(const std::string& name) {
    for (const auto& scenario: config["scenarios"]) {
        std::string scenario_name = scenario.first.as<std::string>();
        if (scenario_name == name)
            return true;
    }

    return false;
}

std::vector<std::string> ScenarioFileHandler::get_names() {
    std::vector<std::string> list;

    std::transform(config["scenarios"].begin(), config["scenarios"].end(), list.begin(),
                   [](const auto& node) { return node.first.template as<std::string>(); });

    return list;
}

void ScenarioFileHandler::get_scenario(GameWorld& game, const std::string& name) {

    YAML::Node node = config["scenarios"][name];

    auto w = node["width"].as<float>();
    auto h = node["height"].as<float>();

    game.set_dimensions(h, w);

    for (const auto& worm: node["worms"]) {
        float x = worm["pos_x"].as<float>();
        float y = worm["pos_y"].as<float>();

        game.create_worm(x, y);
    }

    for (const auto& beam: node["beams"]) {
        auto type = beam["type"].as<std::string>();
        auto x = beam["pos_x"].as<float>();
        auto y = beam["pos_y"].as<float>();
        auto angle = beam["angle"].as<float>();

        if (type == "large")
            game.create_large_beam(x, y, angle);
        else
            game.create_short_beam(x, y, angle);
    }
}
