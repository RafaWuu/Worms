#ifndef TEXTURE_CONTROLLER_H
#define TEXTURE_CONTROLLER_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

enum AnimationState {
    WALK,
    // Standing still
    IDLE,
};

class TextureController {
private:
    SDL2pp::Renderer& renderer;
    std::map<AnimationState, std::shared_ptr<SDL2pp::Texture>> textures;
public:
    TextureController(SDL2pp::Renderer& renderer);
    std::shared_ptr<SDL2pp::Texture> get_texture(AnimationState state);
};

#endif
