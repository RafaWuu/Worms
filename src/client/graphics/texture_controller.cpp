#include "texture_controller.h"

static Uint32 get_color_key();

TextureController::TextureController(SDL2pp::Renderer& renderer_) : renderer(renderer_)
{
    Uint32 color_key = get_color_key();

    SDL2pp::Texture walk(renderer,SDL2pp::Surface("assets/wwalk2.png").SetColorKey(true, color_key));
    textures.emplace(AnimationState::WALK, std::make_shared<SDL2pp::Texture>(std::move(walk)));

    SDL2pp::Texture idle(renderer,SDL2pp::Surface("assets/wblink1.png").SetColorKey(true, color_key));
    textures.emplace(AnimationState::IDLE, std::make_shared<SDL2pp::Texture>(std::move(idle)));

    SDL2pp::Texture jumping(renderer,SDL2pp::Surface("assets/wjumpd.png").SetColorKey(true, color_key));
    textures.emplace(AnimationState::JUMPING, std::make_shared<SDL2pp::Texture>(std::move(jumping)));

    SDL2pp::Texture rolling(renderer,SDL2pp::Surface("assets/wroll.png").SetColorKey(true, color_key));
    textures.emplace(AnimationState::ROLLING, std::make_shared<SDL2pp::Texture>(std::move(rolling)));
}

std::shared_ptr<SDL2pp::Texture> TextureController::get_texture(AnimationState state) {
    return textures[state];
}

// Color del pixel que hay que hacer transparente
static Uint32 get_color_key() {
    SDL2pp::Surface surface("assets/wwalk2.png");
    Uint32 color_key = SDL_MapRGB(surface.Get()->format, 0x80, 0x80, 0xC0);   
    return color_key; 
}
