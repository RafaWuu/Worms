//
// Created by xguss on 21/11/23.
//

#include "scenario_filehandler.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "game/world/server_gameworld.h"

#define SCENARIOS_NODE "scenarios"
#define WORM_WIDTH_NODE "width"
#define WORM_HEIGHT_NODE "height"
#define WORMS_NODE "worms"
#define WORM_POS_X_NODE "pos_x"
#define WORM_POS_Y_NODE "pos_y"
#define BEAMS_NODE "beams"
#define BEAM_POS_X_NODE "pos_x"
#define BEAM_POS_Y_NODE "pos_y"
#define BEAM_TYPE_NODE "type"
#define BEAM_ANGLE_NODE "angle"
#define BEAM_TYPE_LARGE "large"
#define BEAM_FLIP_NODE "flip"


ScenarioFileHandler::ScenarioFileHandler() {
    try {
        config = YAML::LoadFile("../scenarios/scenarios.yaml");

    } catch (const YAML::Exception& e1) {
        try {
            config = YAML::LoadFile("scenarios/scenarios.yaml");

        } catch (const YAML::Exception& e2) {
            std::cerr << "Error yaml: " << e1.what() << std::endl;
            std::cerr << "Error yaml: " << e2.what() << std::endl;
            throw;
        }
    }
}

bool ScenarioFileHandler::scenario_exists(const std::string& name) {
    for (const auto& scenario: config[SCENARIOS_NODE]) {
        std::string scenario_name = scenario.first.as<std::string>();
        if (scenario_name == name)
            return true;
    }

    return false;
}

std::map<std::string, uint16_t> ScenarioFileHandler::get_info() {
    std::map<std::string, uint16_t> map;

    for (auto node: config[SCENARIOS_NODE]) {
        map.emplace(node.first.template as<std::string>(), node.second[WORMS_NODE].size());
    }

    return map;
}

void ScenarioFileHandler::get_scenario(GameWorld& game, const std::string& name) {

    YAML::Node node = config[SCENARIOS_NODE][name];

    auto w = node[WORM_WIDTH_NODE].as<float>();
    auto h = node[WORM_HEIGHT_NODE].as<float>();

    game.set_dimensions(h, w);

    for (const auto& worm: node[WORMS_NODE]) {
        float x = worm[WORM_POS_X_NODE].as<float>();
        float y = worm[WORM_POS_Y_NODE].as<float>();

        game.create_worm(x, y);
    }

    for (const auto& beam: node[BEAMS_NODE]) {
        auto type = beam[BEAM_TYPE_NODE].as<std::string>();
        auto x = beam[BEAM_POS_X_NODE].as<float>();
        auto y = beam[BEAM_POS_Y_NODE].as<float>();
        auto angle = beam[BEAM_ANGLE_NODE].as<float>();
        auto flip = beam[BEAM_FLIP_NODE].as<bool>();

        if (type == BEAM_TYPE_LARGE)
            game.create_large_beam(x, y, flip, angle);
        else
            game.create_short_beam(x, y, flip, angle);
    }
}
