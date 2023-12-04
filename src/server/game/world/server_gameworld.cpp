//
// Created by xguss on 02/11/23.
//

#include "server_gameworld.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

#include "game/entities/server_beam_info.h"
#include "game/entities/server_explosion.h"
#include "game/entities/server_worm_info.h"
#include "game/entities/server_worm_sensor.h"

#include "b2_edge_shape.h"
#include "server_error.h"
#include "server_gameworld_simulationstate.h"
#include "server_gameworld_state_waiting.h"

#define GRAVITY_Y (-9.8)

GameWorld::GameWorld(const std::string& scenario_name):
        b2_world(b2Vec2(.0, GRAVITY_Y)),
        worm_map(),
        file_handler(),
        player_manager(),
        wind(),
        listener(*this),
        provision_factory(*this),
        config(Configuration::get_instance()) {

    entity_id = 0;
    file_handler.get_scenario(*this, scenario_name);

    add_entity(std::make_shared<Ground>(&b2_world, width));

    b2_world.SetContactListener(&listener);
    game_state = std::make_shared<GameWorldWaitingState>(player_manager, *worm_map[0], *this);
}

void GameWorld::create_worm(float x, float y) {
    auto worm = std::make_shared<Worm>(entity_id, *this, x, -y);
    worm_map.emplace(entity_id, worm.get());
    add_entity(worm);
    add_entity(std::make_shared<WormSensor>(worm.get()));
}

void GameWorld::create_large_beam(float x, float y, float angle) {
    add_entity(std::make_shared<Beam>(&b2_world, x, -y, config.beam_large_width, config.beam_height,
                                      angle));
}

void GameWorld::create_short_beam(float x, float y, float angle) {
    add_entity(std::make_shared<Beam>(&b2_world, x, -y, config.beam_small_width, config.beam_height,
                                      angle));
}

void GameWorld::step(int steps) {
    for (int32 i = 0; i < steps; ++i) {
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        b2_world.Step(1.0f / config.get_tick_rate(), 8, 3);
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

    manage_round();
}

void GameWorld::manage_round() {
    this->game_state = this->game_state->update();
    if (!this->game_state)
        throw;  // Todo: Crear error
}

void GameWorld::set_clients_to_worms(const std::vector<uint16_t>& client_vec) {
    player_manager.assign_worms_to_players(client_vec, worm_map);
    int i = 0;

    for (auto& worm: worm_map) {
        if (worm.second == nullptr)
            continue;

        worm.second->set_client_id(client_vec[i % client_vec.size()]);
        i++;
    }

    game_state = std::make_shared<GameWorldSimulationState>(
            player_manager, player_manager.get_next_worm_from_client(), false, *this);
}

Worm& GameWorld::get_worm(uint8_t worm_id, uint16_t client_id) {
    auto it = worm_map.find(worm_id);
    if (it == worm_map.end() || !it->second->validate_client(client_id))
        throw InvalidWormIdGameError(client_id);

    return *it->second;
}

std::map<uint16_t, std::shared_ptr<GameObjectInfo>> GameWorld::get_entities_info() {
    std::map<uint16_t, std::shared_ptr<GameObjectInfo>> map;

    for (auto& e: entities_map) {
        map.emplace(e.first, e.second->get_status());
    }

    return map;
}

std::map<uint16_t, std::shared_ptr<WormInfo>> GameWorld::get_worms_info() {
    std::map<uint16_t, std::shared_ptr<WormInfo>> map;

    for (auto& e: worm_map) {
        map.emplace(e.first, e.second->get_worminfo());
    }

    return map;
}
void GameWorld::get_dimensions(float& h, float& w) {
    h = this->height;
    w = this->width;
}

void GameWorld::add_entity(std::shared_ptr<GameObject> object) {
    entities_map.emplace(entity_id++, object);
}

//  limit 4to cuadrante x>=0 , y<=0
void GameWorld::set_dimensions(float h, float w) {
    width = w;
    height = h;
    boundary = std::make_unique<Boundary>(&b2_world, w, h);
}

GameWorld::~GameWorld() {}

size_t GameWorld::get_worms_number() { return worm_map.size(); }

void GameWorld::notify_explosion(uint16_t projectile_type, float radius, b2Vec2 center) {
    add_entity(std::make_shared<Explosion>(projectile_type, radius, center));
}

void GameWorld::notify_damaged_worm(uint16_t worm_id) { game_state->handle_worm_damaged(worm_id); }

void GameWorld::notify_entity_is_moving() { game_state->handle_entity_moving(); }

void GameWorld::notify_weapon_used() { game_state->handle_weapon_fired(); }


uint16_t GameWorld::get_active_worm() { return game_state->get_active_worm().id; }

void GameWorld::on_new_round() {
    generate_provision();
    update_wind();
}

void GameWorld::generate_provision() {
    if (provision_factory.provision_this_round()) {
        auto provision = provision_factory.generate_provision();
        if (provision != nullptr) {
            add_entity(provision);
        }
    }
}

void GameWorld::update_wind() {
    wind.update_wind();
    std::cout << "Viento: " << wind.wind << '\n';
}

void GameWorld::apply_wind_effect(b2Body& body) { wind.affect_projectile(body); }

float GameWorld::get_wind_value() const { return wind.wind; }

float GameWorld::get_round_remaining_time() { return game_state->get_remaining_time(); }
