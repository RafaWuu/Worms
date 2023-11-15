//
// Created by xguss on 02/11/23.
//

#include "server_gameworld.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

#include "b2_body.h"

#include "game/entities/server_beam_info.h"
#include "game/entities/server_worm_info.h"
#include "game/entities/server_worm_sensor.h"
#include "server_error.h"

GameWorld::GameWorld(const std::string& scenario_name):
        b2_world(b2Vec2(.0, -9.8)),
        worm_map(),
        entities_map(),
        file_handler(scenario_name),
        listener()
{

    bazooka = new Weapon(*this);

    entity_id = 0;

    height = 20.0;
    width = 20.0;

    entities_map.emplace(entity_id++, std::make_shared<Ground>(&b2_world));

    entities_map.emplace(entity_id++, std::make_shared<Beam>(&b2_world, 15, 10, 6, .8, 0));
    entities_map.emplace(entity_id++, std::make_shared<Beam>(&b2_world, 2, 5, 6, .8, 0));


    for (int i = 0; i < 2; ++i) {
        auto worm = std::make_shared<Worm>(entity_id, &b2_world, 2.0 + (float)i * 13.f, 15, *bazooka);
        entities_map.emplace(entity_id, worm);
        worm_map.emplace(entity_id++, worm);

        entities_map.emplace(entity_id++, std::make_shared<WormSensor>(worm.get()));
    }

    b2_world.SetContactListener(&listener);
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
        e.second->update(b2_world);
    }
}

void GameWorld::set_clients_to_worms(std::vector<uint16_t> client_vec) {
    int i = 0;

    for (auto& worm: worm_map) {
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
    if(!it->second->validate_client(client_id))
        throw InvalidWormIdGameError(client_id);

    return *it->second;
}

std::map<uint16_t, std::shared_ptr<GameObjectInfo>> GameWorld::get_entities_info() {
    std::map<uint16_t, std::shared_ptr<GameObjectInfo>> map;

    for (auto& e: entities_map) {
        //  cppcheck-suppress useStlAlgorithm
        map.emplace(e.first, e.second->get_status());
    }

    return std::move(map);
}

GameWorld::~GameWorld() {
    delete bazooka;
}
std::map<uint16_t, std::shared_ptr<WormInfo>> GameWorld::get_worms_info() {
    std::map<uint16_t, std::shared_ptr<WormInfo>> map;

    for (auto& e: worm_map) {
        //  cppcheck-suppress useStlAlgorithm
        map.emplace(e.first, e.second->get_worminfo());
    }

    return std::move(map);
}
void GameWorld::get_dimensions(float* h, float* w) {
    *h = this->height;
    *w = this->width;

}
void GameWorld::add_proyectil(std::shared_ptr<BazookaProyectil> proyectil) {
    entities_map.emplace(entity_id++, proyectil);
}
