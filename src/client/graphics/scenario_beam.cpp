#include "scenario_beam.h"

#include "../game/beam.h"


ScenarioBeam::ScenarioBeam(TextureController& controller, float x, float y, float width,
                           float height, float angle):
        texture_controller(controller), x(x), y(y), width(width), height(height), angle(angle) {
    if (width == 3) {
        texture = controller.get_texture(AnimationState::SCENARIO_BEAM_3M);
    } else {
        texture = controller.get_texture(AnimationState::SCENARIO_BEAM_6M);
    }
}

ScenarioBeam::~ScenarioBeam() {}

void ScenarioBeam::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    // segun el juego, hay una viga en (-3,6)
    // harcodeado, hay q pasar escalar dimensiones
    SDL2pp::Point center;
    center.x = 150 / 2;  // widht*escala /2
    center.y = 50 / 2;   // height*escala /2
    renderer.Copy(*texture, SDL2pp::Rect(0, 0, (*texture).GetWidth(), (*texture).GetHeight()),
                  SDL2pp::Rect((x-6/2) * (640.0 / 20.0),
                                (-y-0.8/2) * (480.0 / 20.0) ,
                               (6 * 640.0 / 20.0),
                                (.8 * 480.0 / 20.0)),
                  angle, center, 0);
}
