

#include "server_ground.h"

#include <iostream>
#include <memory>

#include "box2d/b2_edge_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "server_ground_info.h"


Ground::Ground(b2World* world, float width, float height, float pos_x, float pos_y):
        width(width), height(height), GameObject() {
    b2BodyDef groundBodyDef;
    body = world->CreateBody(&groundBodyDef);

    b2FixtureDef fixtureDef;

    fixtureDef.filter.categoryBits = GROUND;
    fixtureDef.filter.maskBits = WORM_SENSOR | WORM;
    fixtureDef.isSensor = true;

    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    b2EdgeShape edge;

    edge.SetTwoSided(b2Vec2(-width / 2, height / 2), b2Vec2(width / 2, height / 2));
    fixtureDef.shape = &edge;
    body->CreateFixture(&fixtureDef);

    edge.SetTwoSided(b2Vec2(width / 2, height / 2), b2Vec2(width / 2, -height / 2));
    fixtureDef.shape = &edge;
    body->CreateFixture(&fixtureDef);

    edge.SetTwoSided(b2Vec2(width / 2, -height / 2), b2Vec2(-width / 2, -height / 2));
    fixtureDef.shape = &edge;
    body->CreateFixture(&fixtureDef);

    edge.SetTwoSided(b2Vec2(-width / 2, -height / 2), b2Vec2(-width / 2, height / 2));
    fixtureDef.shape = &edge;
    body->CreateFixture(&fixtureDef);

    body->SetTransform(b2Vec2(pos_x, pos_y), 0);
}

ObjectType Ground::get_id() const { return GROUND; }

std::unique_ptr<GameObjectInfo> Ground::get_status() const {
    return std::make_unique<GroundInfo>(*this);
}
