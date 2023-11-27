//
// Created by xguss on 15/11/23.
//

#include "projectile.h"

#include <memory>

#include "graphics/ground_entity.h"
#include "graphics/projectile_entity.h"

float Projectile::get_pos_x() const { return x; }
float Projectile::get_pos_y() const { return y; }
float Projectile::get_angle() const { return angle; }

std::unique_ptr<Entity> Projectile::create(TextureController& controller) {
    return std::make_unique<projectileEntity>(controller);
}

Projectile::Projectile(uint8_t type, float x, float y, float angle): type(type), x(x), y(y), angle(angle) {}
