#include "crosshair.h"

void Crosshair::render_by_angle(SDL2pp::Renderer& renderer, int player_x, int player_y, float aim_angle, Camera& camera) {
    float distance_from_player = 100.0f;
    float x = player_x + distance_from_player * cos(aim_angle) - camera.get_x();
    float y = player_y - distance_from_player * sin(aim_angle) - camera.get_y();

    int crosshair_size = 50;
    x -= crosshair_size / 2; // Ajusto para que el crosshair quede mas centrado
    y -= crosshair_size / 2;   

    SDL_RendererFlip flip = SDL_FLIP_NONE; // No importa la orientacion
    render(renderer, SDL2pp::Rect(x , y, crosshair_size, crosshair_size), flip);
}

void Crosshair::render_by_coordinates(SDL2pp::Renderer& renderer, float x, float y, Camera& camera) {
    int crosshair_size = 50;
    x -= crosshair_size / 2 ; // Ajusto para que el crosshair quede mas centrado
    y -= crosshair_size / 2;   

    SDL_RendererFlip flip = SDL_FLIP_NONE; // No importa la orientacion
    render(renderer, SDL2pp::Rect(x - camera.get_x(), y - camera.get_y(), crosshair_size, crosshair_size), flip);
}
