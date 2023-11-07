//
// Created by xguss on 05/11/23.
//

#include "server_ground.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"

Ground::Ground(b2World* world): GameObject() {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -20.0f);

    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;

    groundBox.SetAsBox(50.0f, 5.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    groundBody->CreateFixture(&fixtureDef);
}

ObjectType Ground::get_id(){
    return BEAM;
}

