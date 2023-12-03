//
// Created by xguss on 30/11/23.
//

#include "server_melee_impact.h"

#include <iostream>
#include <string>
#include <utility>

#include "game/world/server_gameworld.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_melee_impact_info.h"

#define FRAMES_ALIVE 3

MeleeImpact::MeleeImpact(b2World* world, std::string&& identifier, uint16_t owner_id, b2Vec2 center,
                         b2Vec2 direction):
        type(config.get_weapon_id(identifier)),
        config(Configuration::get_instance()),
        direction(direction),
        owner_id(owner_id),
        GameObject() {

    float width = config.get_weapon_width(identifier);
    float height = config.get_weapon_height(identifier);
    this->blast_power = config.get_weapon_blastpower(identifier);
    this->damage = config.get_weapon_damage(identifier);

    b2BodyDef bodyDef;
    bodyDef.position.Set(center.x, center.y);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(width / 2, height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;

    fixtureDef.filter.categoryBits = MELEE_SENSOR;
    fixtureDef.filter.maskBits = WORM;


    fixtureDef.isSensor = true;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    fixtureDef.filter.groupIndex = -(int)projectile;
    body = world->CreateBody(&bodyDef);

    body->CreateFixture(&fixtureDef);
    body->SetBullet(true);
    body->SetAwake(true);

    had_impacted = false;

    frames = FRAMES_ALIVE;
}

void MeleeImpact::update(GameWorld& world) {
    frames--;

    if (frames < 0 || had_impacted)
        is_dead = true;

    if (is_dead) {
        return;
    }

    world.notify_entity_is_moving();
}

void MeleeImpact::on_impact(GameWorld& world, Worm& worm) {
    if (worm.id == owner_id)
        return;

    if (!had_impacted)
        had_impacted = true;

    worm.body->ApplyLinearImpulseToCenter(blast_power * direction, true);
    worm.get_hit(damage);
}

std::unique_ptr<GameObjectInfo> MeleeImpact::get_status() const {
    return std::make_unique<MeleeSensorInfo>(*this);
}
ObjectType MeleeImpact::get_id() const { return MELEE_SENSOR; }

void MeleeImpact::delete_body() { body->GetWorld()->DestroyBody(body); }
