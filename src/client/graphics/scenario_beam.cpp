#include "scenario_beam.h"

#include "../game/beam.h"


ScenarioBeam::ScenarioBeam(TextureController& controller,
                    float x,
                    float y,
                    float width,
                    float height,
                    float angle):
                    texture_controller(controller),
                    x(x),
                    y(y),
                    width(width),
                    height(height),
                    angle(angle)
    {if (width == 3){
        texture = controller.get_texture(AnimationState::SCENARIO_BEAM_3M);
    }else{
        texture = controller.get_texture(AnimationState::SCENARIO_BEAM_6M);
    }
    }

ScenarioBeam::~ScenarioBeam() {}

void ScenarioBeam::render(SDL2pp::Renderer& renderer) {
    //segun el juego, hay una viga en (-3,6)
    //harcodeado, hay q pasar escalar dimensiones
    
    renderer.Copy(
            *texture,
            SDL2pp::Rect(0, 0,(*texture).GetWidth(),(*texture).GetHeight()),
            SDL2pp::Rect(x*(320/20)+320, y* (240 / 20) + 240, 150,50),
            angle,
            SDL2pp::NullOpt,
            0);

}