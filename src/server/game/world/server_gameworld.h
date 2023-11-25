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
#include "game/weapons/server_bazooka_proyectil.h"
#include "game/weapons/server_weapon.h"

#include "b2_world.h"
#include "scenario_filehandler.h"

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
    void add_proyectil(std::shared_ptr<BazookaProyectil> proyectil);
    void apply_blast_impulse(b2Body* body, Worm* worm, const b2Vec2& blastCenter, const b2Vec2& applyPoint,
                             float blastPower);
    void add_explosion(b2Body& proyectil, float radius);
};
#endif  // WORMS_SERVER_GAMEWORLD_H
