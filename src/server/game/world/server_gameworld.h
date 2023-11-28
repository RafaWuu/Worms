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
#include "game/projectiles/server_projectile.h"
#include "game/weapons/server_weapon.h"
#include "game/entities/server_boundary.h"

#include "b2_world.h"
#include "scenario_filehandler.h"

class Weapon;

class GameWorld {
private:
    ScenarioFileHandler file_handler;

    std::map<uint16_t, Worm*> worm_map;
    std::map<uint16_t, std::shared_ptr<GameObject>> entities_map;

    uint16_t entity_id;
    OnFloorContactListener listener;
    double height;
    double width;
    std::unique_ptr<Boundary> boundary;
    Configuration& config;

public:
    b2World b2_world;
    explicit GameWorld(const std::string& scenario_name);
    ~GameWorld();
    GameWorld(const GameWorld&) = delete;
    GameWorld& operator=(const GameWorld&) = delete;

    void set_dimensions(float h, float w);
    void get_dimensions(float* h, float* w);

    void create_worm(float x, float y);
    void create_large_beam(float x, float y, float angle);
    void create_short_beam(float x, float y, float angle);

    void step(int steps);
    void update_entities();

    void set_clients_to_worms(const std::vector<uint16_t>& client_vec);
    std::map<uint16_t, std::shared_ptr<GameObjectInfo>> get_entities_info();
    std::map<uint16_t, std::shared_ptr<WormInfo>> get_worms_info();

    Worm& get_worm(uint8_t worm_id, uint16_t client_id);
    void add_projectile(std::shared_ptr<Projectile> projectile);

    size_t get_worms_number();

    void notify_explosion(uint16_t projectile_type, float radius, b2Vec2 center);
};
#endif  // WORMS_SERVER_GAMEWORLD_H
