#include "server_boundary.h"

#include "b2_body.h"
#include "b2_edge_shape.h"
#include "b2_fixture.h"
Boundary::Boundary(b2World* b2_world, float width, float height):
        width(width), height(height), GameObject() {

    b2Vec2 top_left(0, 0);
    b2Vec2 top_right(width, 0);
    b2Vec2 bottom_left(0, -height);
    b2Vec2 bottom_right(width, -height);


    b2BodyDef body_def;
    b2FixtureDef fixture_def;
    fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

    fixture_def.filter.categoryBits = BOUNDARY;
    fixture_def.filter.maskBits =
            WORM | WORM_SENSOR | projectile | BEAM | EXPLOSION | MELEE_SENSOR | PROVISION_SENSOR;

    body_def.type = b2_staticBody;
    body_def.position.Set(0, 0);

    b2EdgeShape edge_shape;

    edge_1 = b2_world->CreateBody(&body_def);
    edge_shape.SetTwoSided(top_left, top_right);
    fixture_def.shape = &edge_shape;
    // edge_1->CreateFixture(&fixture_def);

    edge_2 = b2_world->CreateBody(&body_def);
    edge_shape.SetTwoSided(top_left, bottom_left);
    fixture_def.shape = &edge_shape;
    edge_2->CreateFixture(&fixture_def);

    edge_3 = b2_world->CreateBody(&body_def);
    edge_shape.SetTwoSided(top_right, bottom_right);
    fixture_def.shape = &edge_shape;
    edge_3->CreateFixture(&fixture_def);
}

ObjectType Boundary::get_id() const { return BOUNDARY; }

std::unique_ptr<GameObjectInfo> Boundary::get_status() const { return nullptr; }