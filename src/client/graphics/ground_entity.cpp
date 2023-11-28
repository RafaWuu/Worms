//
// Created by xguss on 14/11/23.
//

#include "ground_entity.h"
GroundEntity::GroundEntity(TextureController controller, uint16_t x, uint16_t y, uint16_t w,
                           uint16_t h):
        texture_controller(controller),
        x(x),
        y(y),
        width(w),
        height(h),
        texture(controller.get_texture(AnimationState::IDLE)) {}

void GroundEntity::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    renderer.FillCopy(*texture, SDL2pp::NullOpt,
                      SDL2pp::Rect(x - width / 2, y - width / 2, width, height));
}
void GroundEntity::update_info(EntityInfo* info) { Entity::update_info(info); }
