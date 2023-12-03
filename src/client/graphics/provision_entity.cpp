//
// Created by xguss on 03/12/23.
//

#include "provision_entity.h"

ProvisionEntity::ProvisionEntity(TextureController& controller, uint16_t x, uint16_t y,
                                 uint16_t width, uint16_t height):
        texture_controller(controller), x(x), y(y), width(width), height(height) {

    texture = controller.get_texture(AnimationState::IDLE);
}

ProvisionEntity::~ProvisionEntity() {}

void ProvisionEntity::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    int offsetX = 1.58 * 25;
    int offsetY = -1.4 * 25;

    renderer.Copy(*texture, SDL2pp::Rect(0, 0, (*texture).GetWidth(), (*texture).GetHeight()),
                  SDL2pp::Rect(x - width / 2 + offsetX, y - height / 2 + offsetY, width, height), 0,
                  SDL2pp::NullOpt, 0);
}