//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_GAMEWORLD_H
#define WORMS_SERVER_GAMEWORLD_H

#include <map>
#include <string>
#include <vector>

#include "../../Box2D/b2_world.h"

#include "server_beam.h"
#include "server_beam_info.h"
#include "server_scenario_file_handler.h"
#include "server_worm.h"
#include "server_worm_info.h"

class GameWorld {
private:
    ScenarioFileHandler file_handler;
    b2World b2_world;

    std::map<uint16_t, Worm> worm_map;
    std::vector<Beam> beam_vec;

public:
    explicit GameWorld(const std::string& scenario_name);
    void step(int steps);

    void update_worms();

    void set_clients_to_worms(std::vector<uint16_t> client_vec);

    Worm* get_worm(uint8_t worm_id);

    std::vector<WormInfo> get_worms_info();

    std::vector<BeamInfo> get_beams_info();
};
#endif  // WORMS_SERVER_GAMEWORLD_H
