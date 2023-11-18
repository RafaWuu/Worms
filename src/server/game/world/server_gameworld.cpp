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
#include "server_error.h"

GameWorld::GameWorld(const std::string& scenario_name):
        b2_world(b2Vec2(.0, -9.8)),
        worm_map(),
        entities_map(),
        file_handler(scenario_name),
        listener(*this) {

    bazooka = new Weapon(*this);

    entity_id = 0;

    height = 20.0;
    width = 20.0;

    set_dimensions();
    entities_map.emplace(entity_id++, std::make_shared<Ground>(&b2_world));

    entities_map.emplace(entity_id++, std::make_shared<Beam>(&b2_world, 15, 10, 6, .8, 0));
    entities_map.emplace(entity_id++, std::make_shared<Beam>(&b2_world, 2, 5, 6, .8, 0));


    for (int i = 0; i < 2; ++i) {
        auto worm =
                std::make_shared<Worm>(entity_id, &b2_world, 2.0 + (float)i * 13.f, 15, *bazooka);
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

    for (auto it = entities_map.cbegin(); it != entities_map.cend();) {
        if (it->second->is_dead)
            it = entities_map.erase(it);
        else
            ++it;
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

GameWorld::~GameWorld() { delete bazooka; }
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
void GameWorld::add_proyectil(std::shared_ptr<BazookaProyectil> proyectil) {
    entities_map.emplace(entity_id++, proyectil);
}

//  limit 4to cuadrante x>=0 , y<=0
void GameWorld::set_dimensions() {
    b2Vec2 top_left(0, 0);
    b2Vec2 top_right(width, 0);
    b2Vec2 bottom_left(0, -height);
    b2Vec2 bottom_right(width, -height);

    /*
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
    edge_3->CreateFixture(&fixture_def);

    b2Body* edge_4 = b2_world.CreateBody(&body_def);
    edge_shape.SetTwoSided(bottom_left, bottom_right);
    fixture_def.shape = &edge_shape;
    edge_4->CreateFixture(&fixture_def);
     */
}

void GameWorld::add_explosion(b2Body& proyectil, float radius) {
    b2Vec2 center = proyectil.GetPosition();
    int num_rays = 15;
    float m_blastPower = 30;
    for (int i = 0; i < num_rays; i++) {
        float angle = (i / (float)num_rays) * 2 * M_PI;

        b2Vec2 rayDir(sinf(angle), cosf(angle));
        b2Vec2 rayEnd = center + radius * rayDir;

        // check what this ray hits
        RayCastExplosionCallback callback;
        b2_world.RayCast(&callback, center, rayEnd);
        if (callback.m_body && callback.p_worm) {
            apply_blast_impulse(callback.m_body, callback.p_worm, center, callback.m_point,
                                (m_blastPower / (float)num_rays));
        }
    }
}

void GameWorld::apply_blast_impulse(b2Body* body, Worm* worm, b2Vec2 blastCenter, b2Vec2 applyPoint,
                                    float blastPower) {
    b2Vec2 blastDir = applyPoint - blastCenter;
    float distance = blastDir.Normalize();
    // ignore bodies exactly at the blast point - blast direction is undefined
    if (distance == 0)
        return;
    float invDistance = 1 / distance;
    float impulseMag = blastPower * invDistance * invDistance;
    impulseMag = b2Min(impulseMag, 500.0f);

    body->ApplyLinearImpulse(impulseMag * blastDir, applyPoint, true);
    worm->get_hit(50 * invDistance);
}
