//
// Created by xguss on 14/11/23.
//
#include "ground.h"

#include "graphics/debug_entity.h"

float Ground::get_pos_x() const { return x; }
float Ground::get_pos_y() const { return y; }

std::unique_ptr<Entity> Ground::create(TextureController& controller) {
    return std::make_unique<DebugEntity>(controller, x, y, width, height);
}

Ground::Ground(float x, float y, float height, float width):
        x(x), y(y), height(height), width(width){
}
