
#include "server_beam.h"

#include <memory>

#include "box2d/b2_body.h"
#include "box2d/b2_edge_shape.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "server_beam_info.h"

#define MAX_ANGLE 90.01
#define WALKABLE_ANGLE 45

#define WALKABLE_FRICTION .5
#define NO_WALKABLE_FRICTION .1

Beam::Beam(b2World* b2_world, float center_x, float center_y, float width, float height, bool flip,
           float angle):
        pos_x(center_x), pos_y(center_y), width(width), height(height), angle(angle), GameObject() {

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    body = b2_world->CreateBody(&bodyDef);


    b2FixtureDef fixtureDef;

    this->angle = fmod(this->angle, MAX_ANGLE);
    fixtureDef.friction = this->angle < WALKABLE_ANGLE ? WALKABLE_FRICTION : NO_WALKABLE_FRICTION;

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

bool Beam::is_walkable() { return abs(angle) < WALKABLE_ANGLE; }
