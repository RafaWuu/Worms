//
// Created by xguss on 14/11/23.
//

#include "server_projectile.h"

#include <iostream>
#include <string>
#include <utility>

#include "game/world/server_gameworld.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_projectile_effect.h"
#include "server_projectile_info.h"

Projectile::Projectile(b2World* world, std::string&& identifier,
                       std::unique_ptr<ProjectileEffect> impact_strategy,
                       std::unique_ptr<ProjectileEffect> countdown_strategy, b2Vec2 pos,
                       float angle, float power, float countdown):
        type(config.get_weapon_id(identifier)),
        impact_strategy(std::move(impact_strategy)),
        countdown_strategy(std::move(countdown_strategy)),
        config(Configuration::get_instance()),
        GameObject() {

    this->countdown = countdown;
    this->width = config.get_weapon_width(identifier);
    this->height = config.get_weapon_height(identifier);
    this->dragConstant = config.get_weapon_dragconstant(identifier);
    float density = config.get_weapon_density(identifier);
    float angular_damping = config.get_weapon_damping(identifier);
    float max_vel = config.get_weapon_max_vel(identifier);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0, 510);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(width / 2, height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = density;

    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    fixtureDef.filter.groupIndex = -(int)projectile;
    body = world->CreateBody(&bodyDef);

    body->CreateFixture(&fixtureDef);
    body->SetAngularDamping(angular_damping);
    body->SetBullet(true);

    body->SetAwake(true);
    body->SetAngularVelocity(0);
    body->SetTransform(pos, angle);
    body->SetLinearVelocity(body->GetWorldVector(b2Vec2(power * max_vel, 0)));
    had_impacted = false;
}

void Projectile::update(GameWorld& world) {
    if (had_impacted) {
        is_dead = impact_strategy->execute(world, *this->body);
    }
    if (is_dead)
        return;

    b2Vec2 flightDirection = body->GetLinearVelocity();
    float flightSpeed = flightDirection.Normalize();
    b2Vec2 pointingDirection = body->GetWorldVector(b2Vec2(1, 0));
    float dot = b2Dot(flightDirection, pointingDirection);

    float dragForceMagnitude =
            (1 - fabs(dot)) * flightSpeed * flightSpeed * dragConstant * body->GetMass();

    b2Vec2 tailPosition = body->GetWorldPoint(b2Vec2(-width / 2, 0));

    body->ApplyForce(dragForceMagnitude * -flightDirection, tailPosition, true);

    countdown -= 1.0 / config.get_tick_rate();

    std::cout << "countdown: " << countdown << '\n';

    if (countdown < 0.0)
        on_countdown_finished(world);
}


std::unique_ptr<GameObjectInfo> Projectile::get_status() const {
    return std::make_unique<ProjectileInfo>(*this);
}
ObjectType Projectile::get_id() const { return projectile; }

void Projectile::on_projectile_impact(GameWorld& world) {
    if (!had_impacted)
        had_impacted = true;
}

void Projectile::on_countdown_finished(GameWorld& world) {
    is_dead = countdown_strategy->execute(world, *this->body);
}

void Projectile::delete_body() { body->GetWorld()->DestroyBody(body); }
