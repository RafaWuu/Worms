#include "wind.h"

Wind::Wind(TextureController& texture_controller, float wind) : texture_controller(texture_controller), wind(wind) {
    left_wind = texture_controller.get_texture(LEFT_WIND);
    right_wind = texture_controller.get_texture(RIGHT_WIND);

    Configuration& config = Configuration::get_instance();

    max_wind = config.get_max_wind();
    min_wind = config.get_min_wind();

    numFrames = left_wind->GetWidth() / left_wind->GetHeight();
    size = left_wind->GetHeight();

    x = SCREEN_WIDTH / 2;
    y = SCREEN_HEIGHT - size;
}

void Wind::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    float wind_per_frame = (max_wind - min_wind) / numFrames;

    if (wind > 0) {
        int frames_to_draw = wind / wind_per_frame;

        // x2 para que se vea mejor
        int width_to_draw = std::max(1, frames_to_draw) * size * 2;

        renderer.Copy(*right_wind, SDL2pp::Rect(0, 0, frames_to_draw * size, size), SDL2pp::Rect(x, y, width_to_draw, size)); 
    } else {
        float current_wind = abs(wind);

        int frames_to_draw = current_wind / wind_per_frame;

        // x2 para que se vea mejor
        int width_to_draw = std::max(1, frames_to_draw) * size * 2;

        renderer.Copy(*left_wind, SDL2pp::Rect(0, 0, frames_to_draw * size, size), SDL2pp::Rect(x - width_to_draw, y, width_to_draw, size)); 
    }
}

void Wind::change_wind(float wind) {
    this->wind = wind;
}