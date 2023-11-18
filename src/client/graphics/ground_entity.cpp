//
// Created by xguss on 14/11/23.
//

#include "ground_entity.h"
GroundEntity::GroundEntity(TextureController controller, float x, float y, float width,
                           float height):
        texture_controller(controller),
        x(x),
        y(y),
        width(width),
        height(height),
        texture(controller.get_texture(AnimationState::IDLE)) {}

void GroundEntity::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    SDL2pp::Point center;

    renderer.FillCopy(*texture, SDL2pp::NullOpt,
                      SDL2pp::Rect((x - width / 2.0) * (640.0 / 20), -(y) * (480.0 / 20) + 480.0,
                                   width * 640.0 / 20, height * 480.0 / 20));
}
void GroundEntity::update_info(EntityInfo* info) { Entity::update_info(info); }
