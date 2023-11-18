//
// Created by xguss on 05/11/23.
//

#include "server_ground.h"

#include <memory>

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_ground_info.h"

Ground::Ground(b2World* world): width(24.0), height(4.0), GameObject() {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(10.0f, -20.0f);

    body = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;

    groundBox.SetAsBox(width / 2, height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    body->CreateFixture(&fixtureDef);
}

ObjectType Ground::get_id() const { return GROUND; }
std::unique_ptr<GameObjectInfo> Ground::get_status() const {
    return std::make_unique<GroundInfo>(*this);
}
