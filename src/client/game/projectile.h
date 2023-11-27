//
// Created by xguss on 15/11/23.
//

#ifndef WORMS_projectile_H
#define WORMS_projectile_H

#include <memory>

#include "entity_info.h"
class Projectile: public EntityInfo {
private:
    float x;
    float y;
    float angle;

public:
    Projectile(uint8_t type, float x, float y, float angle);
    float get_pos_x() const override;
    float get_pos_y() const override;
    float get_angle() const;
    std::unique_ptr<Entity> create(TextureController& controller) override;
    uint8_t type;
};
#endif  // WORMS_projectile_H
