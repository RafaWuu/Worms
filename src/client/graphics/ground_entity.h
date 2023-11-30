//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_GROUND_ENTITY_H
#define WORMS_GROUND_ENTITY_H

#include <memory>

#include "entity.h"

class GroundEntity: public Entity {
private:
    TextureController& texture_controller;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    std::shared_ptr<SDL2pp::Texture> texture;

public:
    GroundEntity(TextureController controller, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) override;
    void update_info(EntityInfo* info, SoundController& sound_controller) override;
};
#endif  // WORMS_GROUND_ENTITY_H
