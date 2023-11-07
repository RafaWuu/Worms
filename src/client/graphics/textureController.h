#ifndef TEXTURE_CONTROLLER_H
#define TEXTURE_CONTROLLER_H

#include <SDL2pp/SDL2pp.hh>

class TextureController {
private:
    SDL2pp::Renderer& renderer;
    SDL2pp::Texture walking_sprite;
public:
    TextureController(SDL2pp::Renderer& renderer);
    SDL2pp::Texture& get_walking_sprite();
};

#endif
