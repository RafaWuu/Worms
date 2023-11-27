//
// Created by xguss on 02/11/23.
//

#include "server_gameworld.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

#include "game/entities/server_beam_info.h"
#include "game/entities/server_worm_info.h"
#include "game/entities/server_worm_sensor.h"
#include "game/listeners/server_raycast_explosion_callback.h"

#include "b2_body.h"
#include "b2_edge_shape.h"
#include "scenario_filehandler.h"
#include "server_error.h"

GameWorld::GameWorld(const std::string& scenario_name):
        b2_world(b2Vec2(.0, -9.8)), worm_map(), file_handler(), listener(*this) {

    entity_id = 0;
    file_handler.get_scenario(*this, scenario_name);

    entities_map.emplace(entity_id++, std::make_shared<Ground>(&b2_world, width));

    b2_world.SetContactListener(&listener);
}

void GameWorld::create_worm(float x, float y) {
    auto worm = std::make_shared<Worm>(entity_id, *this, x, -y);
    entities_map.emplace(entity_id, worm);
    worm_map.emplace(entity_id++, worm.get());

    entities_map.emplace(entity_id++, std::make_shared<WormSensor>(worm.get()));
}

void GameWorld::create_large_beam(float x, float y, float angle) {
    entities_map.emplace(entity_id++, std::make_shared<Beam>(&b2_world, x, -y, 6, .8, angle));
}

void GameWorld::create_short_beam(float x, float y, float angle) {
    entities_map.emplace(entity_id++, std::make_shared<Beam>(&b2_world, x, -y, 3, .8, angle));
}

void GameWorld::step(int steps) {
    for (int32 i = 0; i < steps; ++i) {
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        b2_world.Step(1.0f / 60.0f, 8, 3);
    }
}

void GameWorld::update_entities() {
    for (auto& e: entities_map) {
        e.second->update(*this);
    }

    for (auto it = entities_map.cbegin(); it != entities_map.cend();) {
        if (it->second->is_dead) {
            it->second->delete_body();
            it = entities_map.erase(it);
        } else {
            ++it;
        }
    }
}

void GameWorld::set_clients_to_worms(std::vector<uint16_t> client_vec) {
    int i = 0;

    for (auto& worm: worm_map) {
        if (worm.second == nullptr)
            continue;

        worm.second->set_client_id(client_vec[i % client_vec.size()]);
        std::cout << "Worm :" << worm.first << ", Client: " << client_vec[i % client_vec.size()]
                  << "\n";
        i++;
    }
}

Worm& GameWorld::get_worm(uint8_t worm_id, uint16_t client_id) {
    auto it = worm_map.find(worm_id);
    if (it == worm_map.end())
        throw InvalidWormIdGameError(client_id);

    if (it->second == nullptr)
        throw InvalidWormIdGameError(client_id);

    if (!it->second->validate_client(client_id))
        throw InvalidWormIdGameError(client_id);

    return *it->second;
}

std::map<uint16_t, std::shared_ptr<GameObjectInfo>> GameWorld::get_entities_info() {
    std::map<uint16_t, std::shared_ptr<GameObjectInfo>> map;

    for (auto& e: entities_map) {
        map.emplace(e.first, e.second->get_status());
    }

    return std::move(map);
}

std::map<uint16_t, std::shared_ptr<WormInfo>> GameWorld::get_worms_info() {
    std::map<uint16_t, std::shared_ptr<WormInfo>> map;

    for (auto& e: worm_map) {
        map.emplace(e.first, e.second->get_worminfo());
    }

    return std::move(map);
}
void GameWorld::get_dimensions(float* h, float* w) {
    *h = this->height;
    *w = this->width;
}
void GameWorld::add_projectile(std::shared_ptr<Projectile> projectile) {
    entities_map.emplace(entity_id++, projectile);
}

//  limit 4to cuadrante x>=0 , y<=0
void GameWorld::set_dimensions(float h, float w) {
    width = w;
    height = h;

    /*
    b2Vec2 top_left(0, 0);
    b2Vec2 top_right(width, 0);
    b2Vec2 bottom_left(0, -height);
    b2Vec2 bottom_right(width, -height);


    b2BodyDef body_def;
    b2FixtureDef fixture_def;
    body_def.type = b2_staticBody;
    body_def.position.Set(0, 0);

    b2EdgeShape edge_shape;

    b2Body* edge_1 = b2_world.CreateBody(&body_def);
    edge_shape.SetTwoSided(top_left, top_right);
    fixture_def.shape = &edge_shape;
    edge_1->CreateFixture(&fixture_def);

    b2Body* edge_2 = b2_world.CreateBody(&body_def);
    edge_shape.SetTwoSided(top_left, bottom_left);
    fixture_def.shape = &edge_shape;
    edge_2->CreateFixture(&fixture_def);

    b2Body* edge_3 = b2_world.CreateBody(&body_def);
    edge_shape.SetTwoSided(top_right, bottom_right);
    fixture_def.shape = &edge_shape;
    edge_3->CreateFixture(&fixture_def);*/
}

void GameWorld::add_explosion(b2Body& projectile, float radius) {}

void GameWorld::apply_blast_impulse(b2Body* body, Worm* worm, b2Vec2 blastCenter, b2Vec2 applyPoint,
                                    float blastPower) {}

GameWorld::~GameWorld() {}
