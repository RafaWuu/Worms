#include "texture_controller.h"

// SetColorKey deberia hacer el background transparente pero no lo hace
TextureController::TextureController(SDL2pp::Renderer& renderer_) : renderer(renderer_)
{
    SDL2pp::Texture walk(renderer,SDL2pp::Surface("assets/wwalk2.png").SetColorKey(true, 0x8080c0));
    textures.emplace(AnimationState::WALK, std::make_shared<SDL2pp::Texture>(std::move(walk)));

    SDL2pp::Texture idle(renderer,SDL2pp::Surface("assets/wblink1.png").SetColorKey(true, 0x8080c0));
    textures.emplace(AnimationState::IDLE, std::make_shared<SDL2pp::Texture>(std::move(idle)));
}

std::shared_ptr<SDL2pp::Texture> TextureController::get_texture(AnimationState state) {
    return textures[state];
}
