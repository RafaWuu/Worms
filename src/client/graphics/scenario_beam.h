#ifndef __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_BEAM_H_
#define __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_BEAM_H_


#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "game/entity_info.h"

#include "entity.h"
#include "texture_controller.h"
#include "camera.h"

class ScenarioBeam: public Entity {
private:
    TextureController& texture_controller;
    std::shared_ptr<SDL2pp::Texture> texture;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    float angle;

public:
    ScenarioBeam(TextureController& texture_controller, uint16_t x, uint16_t y, uint16_t width,
                 uint16_t height, float angle);
    ~ScenarioBeam();


    void render(SDL2pp::Renderer& renderer, Camera& camera) override;
};
#endif  // __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_BEAM_H_