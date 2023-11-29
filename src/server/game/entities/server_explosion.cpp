//
// Created by xguss on 29/11/23.
//

#include "server_explosion.h"

#include "../world/server_gameworld.h"

#include "server_explosion_info.h"

ObjectType Explosion::get_id() const { return EXPLOSION; }

Explosion::Explosion(uint16_t projectile_type, float radius, b2Vec2 center):
        type(projectile_type), radius(radius), pos_x(center.x), pos_y(center.y) {
    frames = 2 * 100;
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
