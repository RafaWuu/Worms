#include "explosion.h"

#include <memory>

#include "graphics/explosion_entity.h"

float Explosion::get_radius() const { return radius; }

std::unique_ptr<Entity> Explosion::create(TextureController& controller) {
    return std::make_unique<ExplosionEntity>(controller, type, radius);
}

Explosion::Explosion(uint8_t type, uint16_t pos_x, uint16_t pos_y, uint16_t width,
                       uint16_t height, float radius):
        type(type), radius(radius), EntityInfo(pos_x, pos_y, width, height) {}
