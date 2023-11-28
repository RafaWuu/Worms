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
protected:
    int x;
    int y;
    int width;
    int height;

public:
    EntityInfo(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height);
    virtual ~EntityInfo() = default;
    uint16_t get_pos_x() const;
    uint16_t get_pos_y() const;
    uint16_t get_height() const;
    uint16_t get_width() const;
    virtual uint16_t get_id() const { return 0; };

    virtual std::unique_ptr<Entity> create(TextureController& controller) = 0;
};
#endif  // WORMS_ENTITY_INFO_H
