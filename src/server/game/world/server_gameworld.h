//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_GAMEWORLD_H
#define WORMS_SERVER_GAMEWORLD_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "game/entities/server_beam.h"
#include "game/entities/server_ground.h"
#include "game/entities/server_worm_sensor.h"
#include "game/listeners/server_onfloor_contactlistener.h"
#include "game/server_scenario_file_handler.h"
#include "game/weapons/server_bazooka_proyectil.h"
#include "game/weapons/server_weapon.h"

#include "b2_world.h"

class Weapon;

class GameWorld {
private:
    ScenarioFileHandler file_handler;
    std::map<uint16_t, std::shared_ptr<Worm>> worm_map;

    std::map<uint16_t, std::shared_ptr<GameObject>> entities_map;
    uint16_t entity_id;
    Weapon* bazooka;
    OnFloorContactListener listener;
    double height;
    double width;

public:
    b2World b2_world;
    explicit GameWorld(const std::string& scenario_name);
    ~GameWorld();
    GameWorld(const GameWorld&) = delete;
    GameWorld& operator=(const GameWorld&) = delete;

    void step(int steps);

    void update_entities();

    void set_clients_to_worms(std::vector<uint16_t> client_vec);

    Worm& get_worm(uint8_t worm_id, uint16_t client_id);
    std::map<uint16_t, std::shared_ptr<GameObjectInfo>> get_entities_info();
    std::map<uint16_t, std::shared_ptr<WormInfo>> get_worms_info();

    void set_dimensions();
    void get_dimensions(float* h, float* w);
    void add_proyectil(std::shared_ptr<BazookaProyectil> proyectil);

    void apply_blast_impulse(b2Body* body, Worm* worm, b2Vec2 blastCenter, b2Vec2 applyPoint,
                             float blastPower);

    void add_explosion(b2Body& proyectil, float radius);
};
#endif  // WORMS_SERVER_GAMEWORLD_H
