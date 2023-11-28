//
// Created by xguss on 15/11/23.
//

#ifndef WORMS_projectile_H
#define WORMS_projectile_H

#include <memory>

#include "entity_info.h"
class Projectile: public EntityInfo {
private:
    float angle;

public:
    Projectile(uint8_t type, uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height,
               float angle);

    float get_angle() const;
    std::unique_ptr<Entity> create(TextureController& controller) override;
    uint8_t type;
};
#endif  // WORMS_projectile_H
