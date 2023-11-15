//
// Created by xguss on 15/11/23.
//

#ifndef WORMS_PROYECTIL_H
#define WORMS_PROYECTIL_H

#include "entity_info.h"
class Proyectil : public EntityInfo {
private:
    float x;
    float y;

public:
    Proyectil(uint8_t type, float x, float y);
    float get_pos_x() const override;
    float get_pos_y() const override;
    std::unique_ptr<Entity> create(TextureController &controller) override;
    uint8_t type;
};
#endif  // WORMS_PROYECTIL_H
