//
// Created by xguss on 03/12/23.
//

#include "provision_entity.h"

ProvisionEntity::ProvisionEntity(TextureController& controller, uint16_t x, uint16_t y,
                                 uint16_t width, uint16_t height):
        texture_controller(controller),
        x(x),
        y(y),
        width(width),
        height(height),
        an(texture_controller.get_texture(CRATE), texture_controller) {}

ProvisionEntity::~ProvisionEntity() {}

void ProvisionEntity::update_info(EntityInfo* info, SoundController& sound_controller) {
    x = info->get_pos_x();
    y = info->get_pos_y();
}

void ProvisionEntity::update(float dt) { an.update(dt); }

void ProvisionEntity::render(SDL2pp::Renderer& renderer, Camera& camera) {
    int offsetX = 0;
    int offsetY = 0;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    an.render(renderer,
              SDL2pp::Rect(x - camera.get_x() - width * 3 / 2 + offsetX, y - camera.get_y() -  height * 3 / 2 + offsetY, width * 3,
                           height * 3),
              flip, 0.0);
}
