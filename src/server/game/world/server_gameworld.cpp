//
// Created by xguss on 02/11/23.
//

#include "server_gameworld.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

#include "b2_body.h"
#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "game/entities/server_beam_info.h"
#include "game/entities/server_worm_info.h"
#include "game/listeners/server_onfloor_contactlistener.h"
#include "game/entities/server_worm_sensor.h"
#include "server_error.h"

GameWorld::GameWorld(const std::string& scenario_name):
        b2_world(b2Vec2(.0, -9.8)),
        worm_map(),
        worm_sensor_map(),
        beam_vec(),
        file_handler(scenario_name),
        listener(),
        ground(&b2_world) {


    for (int i = 0; i < 1; ++i) {
        beam_vec.emplace_back(&b2_world, -3, 6, 6, .8, 15);
    }

    for (int i = 0; i < 2; ++i) {
        auto* worm = new Worm(i, &b2_world, -10.3f + (float)i * 20.f, 4.11);
        auto* sensor = new WormSensor(worm);
        worm_map.insert({i, worm});
        worm_sensor_map.insert({i, sensor});
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

void GameWorld::update_worms() {
    for (auto& worm: worm_map) {
        worm.second->update(&b2_world);
    }
}

void GameWorld::set_clients_to_worms(std::vector<uint16_t> client_vec) {
    int i = 0;

    for (auto& worm: worm_map) {
        worm.second->set_client_id(client_vec[i % client_vec.size()]);
        std::cout << "Worm :" << worm.first << ", Client: " << client_vec[i % worm_map.size()]
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

std::vector<WormInfo> GameWorld::get_worms_info() {
    std::vector<WormInfo> w;

    for (auto& worm: worm_map) {
        //  cppcheck-suppress useStlAlgorithm
        w.emplace_back(*worm.second);
    }

    return std::move(w);
}

std::vector<BeamInfo> GameWorld::get_beams_info() {
    std::vector<BeamInfo> b;

    for (auto& beam: beam_vec) {
        // cppcheck-suppress useStlAlgorithm
        b.emplace_back(beam);
    }

    return std::move(b);
}

GameWorld::~GameWorld() {
    for (auto& w: worm_map) {
        delete w.second;
    }

    for (auto& w: worm_sensor_map) {
        delete w.second;
    }
}
