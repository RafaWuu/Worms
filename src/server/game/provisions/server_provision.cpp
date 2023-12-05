//
// Created by xguss on 30/11/23.
//

#include "server_provision.h"

#include <iostream>
#include <memory>
#include <utility>

#include "../world/server_gameworld.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_provision_info.h"

#define PROV_GRAVITY_SCALE .7

Provision::Provision(GameWorld& world, float x, float y, std::unique_ptr<ProvisionEffect> effect):
        effect(std::move(effect)), config(Configuration::get_instance()) {

    float width = config.provision_width;
    float height = config.provision_height;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(width / 2, height / 2);

    body = world.b2_world.CreateBody(&bodyDef);
    body->SetGravityScale(PROV_GRAVITY_SCALE);

    b2FixtureDef fixtureDefSensor;

    fixtureDefSensor.shape = &polygonShape;
    fixtureDefSensor.density = 1;

    fixtureDefSensor.filter.categoryBits = PROVISION_SENSOR;
    fixtureDefSensor.filter.maskBits = WORM;

    fixtureDefSensor.isSensor = true;
    fixtureDefSensor.userData.pointer = reinterpret_cast<uintptr_t>(this);

    body->CreateFixture(&fixtureDefSensor);

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &polygonShape;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    fixtureDef.filter.categoryBits = PROVISION;
    fixtureDef.filter.maskBits = BEAM | GROUND;

    body->CreateFixture(&fixtureDef);

    body->SetAwake(true);

    been_took = false;
}

void Provision::update(GameWorld& world) {}

ObjectType Provision::get_id() const { return PROVISION; }

void Provision::delete_body() { body->GetWorld()->DestroyBody(body); }

std::unique_ptr<GameObjectInfo> Provision::get_status() const {
    return std::make_unique<ProvisionInfo>(*this);
}

void Provision::take(GameWorld& world, Worm& worm) {
    if (is_dead)
        return;

    effect->take(world, *this, worm);
    is_dead = true;
}
