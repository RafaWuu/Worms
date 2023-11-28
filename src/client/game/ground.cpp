//
// Created by xguss on 14/11/23.
//
#include "ground.h"

#include <memory>

#include "graphics/ground_entity.h"


std::unique_ptr<Entity> Ground::create(TextureController& controller) {
    return std::make_unique<GroundEntity>(controller, x, y, width, height);
}

Ground::Ground(uint16_t x, uint16_t y, uint16_t width, uint16_t height):
        EntityInfo(x, y, width, height) {}
