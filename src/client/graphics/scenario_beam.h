#ifndef __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_BEAM_H_
#define __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_BEAM_H_


#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "game/entity_info.h"

#include "entity.h"
#include "texture_controller.h"

class ScenarioBeam: public Entity {
private:
    TextureController& texture_controller;
    std::shared_ptr<SDL2pp::Texture> texture;
    float x;
    float y;
    float width;
    float height;
    float angle;

public:
    ScenarioBeam(TextureController& texture_controller, float x, float y, float width, float height,
                 float angle);
    ~ScenarioBeam();
    void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) override;
};
#endif  // __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_BEAM_H_