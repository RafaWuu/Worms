//
// Created by xguss on 03/11/23.
//

#include "server_beam.h"

#include "b2_body.h"
#include "b2_fixture.h"
#include "b2_polygon_shape.h"

Beam::Beam(b2World* b2_world, float center_x, float center_y, float width, float height,
           float angle):
        pos_x(center_x), pos_y(center_y), width(width), height(height), angle(angle), GameObject() {

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(center_x, center_y);
    body = b2_world->CreateBody(&bodyDef);

    body->SetTransform(body->GetWorldCenter(), angle);

    b2PolygonShape beam;
    beam.SetAsBox(width / 2, height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &beam;

    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);


    body->CreateFixture(&fixtureDef);
}

ObjectType Beam::get_id() { return BEAM; }
