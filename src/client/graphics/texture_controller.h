#ifndef TEXTURE_CONTROLLER_H
#define TEXTURE_CONTROLLER_H

#include <map>
#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "client_constants.h"
enum AnimationState {
    WALK,
    // Standing still
    IDLE,
    JUMPING,
    ROLLING,
    // Scenario
    SCENARIO_BEAM_3M,
    SCENARIO_BEAM_6M,
    SCENARIO_GROUND,
};

class TextureController {
private:
    SDL2pp::Renderer& renderer;
    std::map<AnimationState, std::shared_ptr<SDL2pp::Texture>> textures;

public:
    explicit TextureController(SDL2pp::Renderer& renderer);
    std::shared_ptr<SDL2pp::Texture> get_texture(AnimationState state);
};

#endif
