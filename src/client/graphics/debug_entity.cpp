//
// Created by xguss on 14/11/23.
//

#include "debug_entity.h"
DebugEntity::DebugEntity(TextureController controller,
                         float x, float y, float width, float height) :
        texture_controller(controller),
        x(x),
        y(y),
        width(width),
        height(height) {
    if (width == 3)
        texture = controller.get_texture(AnimationState::SCENARIO_BEAM_3M);
    else
        texture = controller.get_texture(AnimationState::SCENARIO_BEAM_6M);

}
void DebugEntity::render(SDL2pp::Renderer& renderer) {
    SDL2pp::Point center;
    center.x = 150/2;  //widht*escala /2
    center.y = 50/2;   //height*escala /2

    renderer.Copy(
            *texture,
            SDL2pp::Rect(0, 0,(*texture).GetWidth(),(*texture).GetHeight()),
            SDL2pp::Rect(x*(640/20), -y* (480 / 20) + 480 + 50, 150,50),
            0,
            center,
            0);
}
void DebugEntity::update_info(EntityInfo* info) {
    Entity::update_info(info);
}
