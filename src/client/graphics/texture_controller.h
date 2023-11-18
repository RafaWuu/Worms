#ifndef TEXTURE_CONTROLLER_H
#define TEXTURE_CONTROLLER_H

#include <map>
#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "client_constants.h"
enum AnimationState {
    CROSSHAIR,
    WALKING,
    IDLE,
    JUMPING,
    ROLLING,
    // Scenario
    SCENARIO_BEAM_3M,
    SCENARIO_BEAM_6M,
    SCENARIO_GROUND,
    SCENARIO_BACKGROUND,
    // Weapons
    BAZOOKA_IDLE, // El gusano empieza con una bazooka, empieza con esta textura
    BAZOOKA_AIMING,
    BAZOOKA_PROJECTILE,
};

class TextureController {
private:
    SDL2pp::Renderer& renderer;
    std::map<AnimationState, std::shared_ptr<SDL2pp::Texture>> textures;

public:
    explicit TextureController(SDL2pp::Renderer& renderer);
    std::shared_ptr<SDL2pp::Texture> get_texture(AnimationState state);
    void load_texture(AnimationState state, const std::string& file_name, Uint32 color_key);
};

#endif
