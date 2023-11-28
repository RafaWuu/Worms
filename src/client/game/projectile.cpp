//
// Created by xguss on 15/11/23.
//

#include "projectile.h"

#include <memory>

#include "graphics/ground_entity.h"
#include "graphics/projectile_entity.h"

float Projectile::get_angle() const { return angle; }

std::unique_ptr<Entity> Projectile::create(TextureController& controller) {
    return std::make_unique<projectileEntity>(controller);
}

Projectile::Projectile(uint8_t type, uint16_t pos_x, uint16_t pos_y, uint16_t width,
                       uint16_t height, float angle):
        type(type), angle(angle), EntityInfo(pos_x, pos_y, width, height) {}
