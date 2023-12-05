//
// Created by xguss on 14/11/23.
//

#include "ground_entity.h"
GroundEntity::GroundEntity(TextureController& controller, uint16_t x, uint16_t y, uint16_t w,
                           uint16_t h):
        texture_controller(controller),
        x(x),
        y(y),
        width(w),
        height(h),
        texture(controller.get_texture(SCENARIO_GROUND)) {}

void GroundEntity::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    int h = texture_controller.get_ground_height(y - height / 2);
    int w = texture_controller.get_ground_width(x - width / 2);

    renderer.FillCopy(*texture, SDL2pp::NullOpt, SDL2pp::Rect(x - width / 2, y - height / 2, w, h));
}
void GroundEntity::update_info(EntityInfo* info, SoundController& sound_controller) {
    Entity::update_info(info, sound_controller);
}
