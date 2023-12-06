

#include "server_explosion.h"

#include <memory>

#include "../world/server_gameworld.h"

#include "server_explosion_info.h"

#define EXPLOSION_LIFESPAN 2

ObjectType Explosion::get_id() const { return EXPLOSION; }

Explosion::Explosion(uint16_t projectile_type, float radius, b2Vec2 center):
        type(projectile_type), radius(radius), pos_x(center.x), pos_y(center.y) {
    frames = EXPLOSION_LIFESPAN * Configuration::get_instance().get_tick_rate();
}

void Explosion::update(GameWorld& world) {
    frames--;
    if (frames < 0)
        is_dead = true;

    world.notify_entity_is_moving();
}

std::unique_ptr<GameObjectInfo> Explosion::get_status() const {
    return std::make_unique<ExplosionInfo>(*this);
}
