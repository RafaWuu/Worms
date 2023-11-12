#ifndef __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_BEAM_H_
#define __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_BEAM_H_


# include "texture_controller.h"
#include <SDL2pp/SDL2pp.hh>
#include "texture_controller.h"
#include <vector>

class ScenarioBeam
{
private:
    TextureController& texture_controller;
    std::shared_ptr<SDL2pp::Texture> texture;
    float x;
    float y;
    float width;
    float height;
    float angle;
public:
    ScenarioBeam(TextureController& texture_controller,
        float x, float y, float width, float height, float angle);
    ~ScenarioBeam();
    void render(SDL2pp::Renderer& renderer);

};
#endif // __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_BEAM_H_