//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_ENTITY_INFO_H
#define WORMS_ENTITY_INFO_H

#include <cstdint>
#include <memory>

#include "graphics/texture_controller.h"

class Entity;

class EntityInfo {
public:
    virtual float get_pos_x() const = 0;
    virtual float get_pos_y() const = 0;
    virtual uint16_t get_id() const {
            return 0;
    };

    virtual std::unique_ptr<Entity> create(TextureController& controller) = 0;
};
#endif  // WORMS_ENTITY_INFO_H
