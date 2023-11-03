//
// Created by xguss on 02/11/23.
//

#include "server_gameworld.h"

#include <algorithm>
#include <iostream>
#include <utility>

#include "../../Box2D/b2_body.h"
#include "../../Box2D/b2_fixture.h"
#include "../../Box2D/b2_polygon_shape.h"

#include "server_beam_info.h"
#include "server_worm_info.h"

GameWorld::GameWorld(const std::string& scenario_name):
        b2_world(b2Vec2(.0, -9.8)), worm_map(), beam_vec(), file_handler(scenario_name) {

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = b2_world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;

    // The extents are the half-widths of the box.
    groundBox.SetAsBox(50.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);


    for (int i = 0; i < 1; ++i) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(-10.0f + (float)i * 20, 14.0f);
        b2Body* body = b2_world.CreateBody(&bodyDef);

        b2PolygonShape beam;
        beam.SetAsBox(20.0f, 2.0f);
        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &beam;

        // Set the box density to be non-zero, so it will be dynamic.
        fixtureDef.density = 1.0f;

        // Override the default friction.
        fixtureDef.friction = 0.3f;

        // Add the shape to the body.
        body->CreateFixture(&fixtureDef);
        beam_vec.emplace_back(body, 40, 4, 0);
    }

    for (int i = 0; i < 2; ++i) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(-10.0f + (float)i * 20, 4.0f);
        b2Body* body = b2_world.CreateBody(&bodyDef);

        // Define another box shape for our dynamic body.
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(1.0f, 1.0f);

        // Define the dynamic body fixture.
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;

        // Set the box density to be non-zero, so it will be dynamic.
        fixtureDef.density = 1.0f;

        // Override the default friction.
        fixtureDef.friction = 0.3f;

        // Add the shape to the body.
        body->CreateFixture(&fixtureDef);

        worm_map.emplace(i, Worm(i, body));
    }
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
        worm.second.update(&b2_world);
    }
}

void GameWorld::set_clients_to_worms(std::vector<uint16_t> client_vec) {
    int i = 0;

    for (auto& worm: worm_map) {
        worm.second.set_client_id(client_vec[i]);
        std::cout << "Worm :" << worm.first << ", Client: " << client_vec[i] << "\n";
    }
}

Worm* GameWorld::get_worm(uint8_t worm_id) {
    auto it = worm_map.find(worm_id);
    if (it == worm_map.end())
        return nullptr;

    return &it->second;
}

std::vector<WormInfo> GameWorld::get_worms_info() {
    std::vector<WormInfo> w;

    std::transform(worm_map.begin(), worm_map.end(), w.begin(),
                   [](const auto& worm_pair) { return WormInfo(worm_pair.second); });

    return std::move(w);
}

std::vector<BeamInfo> GameWorld::get_beams_info() {
    std::vector<BeamInfo> b;

    std::transform(beam_vec.begin(), beam_vec.end(), b.begin(),
                   [](const auto& g) { return BeamInfo(g); });

    return std::move(b);
}
