//
// Created by xguss on 03/11/23.
//

#include "server_beam.h"

#include "b2_body.h"
#include "b2_edge_shape.h"
#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_beam_info.h"

Beam::Beam(b2World* b2_world, float center_x, float center_y, float width, float height, bool flip,
           float angle):
        pos_x(center_x), pos_y(center_y), width(width), height(height), angle(angle), GameObject() {

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    body = b2_world->CreateBody(&bodyDef);


    b2FixtureDef fixtureDef;

    this->angle = fmod(this->angle, 90.01);
    fixtureDef.friction = this->angle < 45 ? .5 : .1;

    if (flip)
        this->angle = -this->angle;

    fixtureDef.filter.categoryBits = BEAM;
    fixtureDef.filter.maskBits =
            BOUNDARY | WORM | projectile | PROVISION | BEAM | WORM_SENSOR | EXPLOSION;

    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    b2EdgeShape beam;

    beam.SetTwoSided(b2Vec2(-width / 2, height / 2), b2Vec2(width / 2, height / 2));
    fixtureDef.shape = &beam;
    body->CreateFixture(&fixtureDef);

    beam.SetTwoSided(b2Vec2(width / 2, height / 2), b2Vec2(width / 2, -height / 2));
    fixtureDef.shape = &beam;
    body->CreateFixture(&fixtureDef);

    beam.SetTwoSided(b2Vec2(width / 2, -height / 2), b2Vec2(-width / 2, -height / 2));
    fixtureDef.shape = &beam;
    body->CreateFixture(&fixtureDef);

    beam.SetTwoSided(b2Vec2(-width / 2, -height / 2), b2Vec2(-width / 2, height / 2));
    fixtureDef.shape = &beam;
    body->CreateFixture(&fixtureDef);

    body->SetTransform(b2Vec2(pos_x, pos_y), this->angle * M_PI / 180);
}

ObjectType Beam::get_id() const { return BEAM; }

std::unique_ptr<GameObjectInfo> Beam::get_status() const {
    return std::make_unique<BeamInfo>(*this);
}

bool Beam::is_walkable() { return abs(angle) < 45; }
