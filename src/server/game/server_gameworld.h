//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_GAMEWORLD_H
#define WORMS_SERVER_GAMEWORLD_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../Box2D/b2_world.h"
#include "entities/server_onfloor_contactlistener.h"
#include "game/entities/server_beam.h"
#include "game/entities/server_beam_info.h"
#include "game/entities/server_ground.h"
#include "game/entities/server_worm.h"
#include "game/entities/server_worm_info.h"

#include "server_scenario_file_handler.h"
#include "game/entities/server_worm_sensor.h"

class GameWorld {
private:
    ScenarioFileHandler file_handler;
    b2World b2_world;

    std::map<uint16_t, Worm*> worm_map;
    std::map<uint16_t, WormSensor*> worm_sensor_map;

    std::vector<Beam> beam_vec;

    OnFloorContactListener listener;
    Ground ground;

public:
    explicit GameWorld(const std::string& scenario_name);
    ~GameWorld();

    void step(int steps);

    void update_worms();

    void set_clients_to_worms(std::vector<uint16_t> client_vec);

    Worm* get_worm(uint8_t worm_id);

    std::vector<WormInfo> get_worms_info();

    std::vector<BeamInfo> get_beams_info();
};
#endif  // WORMS_SERVER_GAMEWORLD_H
