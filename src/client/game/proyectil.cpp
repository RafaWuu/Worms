//
// Created by xguss on 15/11/23.
//

#include "proyectil.h"

#include "graphics/debug_entity.h"
#include "graphics/proyectil_entity.h"

float Proyectil::get_pos_x() const { return x; }
float Proyectil::get_pos_y() const { return y; }

std::unique_ptr<Entity> Proyectil::create(TextureController& controller) {
    return std::make_unique<ProyectilEntity>(controller);
}

Proyectil::Proyectil(uint8_t type, float x, float y):
        type(type), x(x), y(y){
}
