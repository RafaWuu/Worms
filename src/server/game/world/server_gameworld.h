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
#include "game/entities/server_boundary.h"
#include "game/entities/server_ground.h"
#include "game/entities/server_worm_sensor.h"
#include "game/listeners/server_contact_listener.h"
#include "game/projectiles/server_projectile.h"
#include "game/weapons/server_weapon.h"

#include "b2_world.h"
#include "scenario_filehandler.h"
#include "server_gameworld_state.h"

class Weapon;

class GameWorld {
private:
    ScenarioFileHandler file_handler;

    std::map<uint16_t, Worm*> worm_map;
    std::map<uint16_t, std::shared_ptr<GameObject>> entities_map;

    uint16_t entity_id;
    ContactListener listener;
    double height;
    double width;
    std::unique_ptr<Boundary> boundary;
    Configuration& config;

    std::shared_ptr<GameWorldState> game_state;

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
    void add_entity(std::shared_ptr<GameObject> object);

    size_t get_worms_number();

    void notify_explosion(uint16_t projectile_type, float radius, b2Vec2 center);

    void manage_round();

    void notify_damaged_worm(uint16_t worm_id);

    void notify_entity_is_moving();

    void notify_weapon_used();

    uint16_t get_active_worm();
};
#endif  // WORMS_SERVER_GAMEWORLD_H
