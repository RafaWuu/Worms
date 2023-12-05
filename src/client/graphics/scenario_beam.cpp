#include "scenario_beam.h"

#include "../game/beam.h"


ScenarioBeam::ScenarioBeam(TextureController& controller, uint16_t x, uint16_t y, uint16_t width,
                           uint16_t height, float angle):
        texture_controller(controller), x(x), y(y), width(width), height(height), angle(angle) {
    if (width == 3) {
        texture = controller.get_texture(AnimationState::SCENARIO_BEAM_3M);
    } else {
        texture = controller.get_texture(AnimationState::SCENARIO_BEAM_6M);
    }
}

ScenarioBeam::~ScenarioBeam() {}

void ScenarioBeam::render(SDL2pp::Renderer& renderer, Camera& camera) {
    // segun el juego, hay una viga en (-3,6)
    // harcodeado, hay q pasar escalar dimensiones
    SDL2pp::Point center;
    center.x = width / 2;   // widht*escala /2
    center.y = height / 2;  // height*escala /2

    int offsetX = 0;
    int offsetY = 0;

    renderer.Copy(*texture, SDL2pp::Rect(0, 0, (*texture).GetWidth(), (*texture).GetHeight()),
                  SDL2pp::Rect(x -camera.get_x() - width / 2 + offsetX, y - camera.get_y() - height / 2 + offsetY, width, height),
                  angle, center, 0);
}
