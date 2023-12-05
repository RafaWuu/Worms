

#include "server_projectile.h"

#include <string>
#include <utility>

#include "game/world/server_gameworld.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_projectile_effect.h"
#include "server_projectile_info.h"

Projectile::Projectile(b2World* world, std::string&& identifier,
                       std::unique_ptr<ProjectileLaunch> launch_strategy,
                       std::unique_ptr<ProjectileEffect> impact_strategy,
                       std::unique_ptr<ProjectileEffect> countdown_strategy, float countdown):
        type(config.get_weapon_id(identifier)),
        impact_strategy(std::move(impact_strategy)),
        countdown_strategy(std::move(countdown_strategy)),
        config(Configuration::get_instance()),
        GameObject() {

    this->countdown = countdown * config.get_tick_rate();
    this->width = config.get_weapon_width(identifier);
    this->height = config.get_weapon_height(identifier);
    this->dragConstant = config.get_weapon_dragconstant(identifier);
    float density = config.get_weapon_density(identifier);
    float restitution = config.get_restitution(identifier);


    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0, 510);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(width / 2, height / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = density;
    fixtureDef.restitution = restitution;

    fixtureDef.filter.categoryBits = projectile;
    fixtureDef.filter.maskBits = WORM | BEAM | GROUND | BOUNDARY;

    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    fixtureDef.filter.groupIndex = -(int)projectile;
    body = world->CreateBody(&bodyDef);

    body->CreateFixture(&fixtureDef);
    body->SetBullet(true);
    body->SetAwake(true);
    body->SetAngularVelocity(0);
    had_impacted = false;

    launch_strategy->execute(*body);
}

void Projectile::update(GameWorld& world) {
    if (had_impacted) {
        is_dead = impact_strategy->execute(world, *this->body);
    }
    if (is_dead)
        return;

    if (config.weapon_is_affected_by_wind(config.get_weapon_name(type)))
        world.apply_wind_effect(*body);

    world.notify_entity_is_moving();  // Si no esta muerta, o se esta moviendo o aun no detono (si
                                      // es granada)

    countdown -= 1;

    if (countdown < 0)
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
