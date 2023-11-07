#include "textureController.h"

// SetColorKey deberia hacer el background transparente pero no lo hace
TextureController::TextureController(SDL2pp::Renderer& renderer_) : renderer(renderer_), 
    walking_sprite(renderer,SDL2pp::Surface("assets/wwalk2.png").SetColorKey(true, 0x8080c0))
    
    {}

SDL2pp::Texture& TextureController::get_walking_sprite() {
    return walking_sprite;
}