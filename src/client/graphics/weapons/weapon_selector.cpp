#include "weapon_selector.h"

WeaponSelector::WeaponSelector(SDL2pp::Renderer& renderer) {
    std::string path = "../assets/weapons.png";
    std::string alternative_path = "assets/weapons.png";

    try {
        texture = std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(path));
    } catch (SDL2pp::Exception& e) {
        texture = std::make_unique<SDL2pp::Texture>(renderer, SDL2pp::Surface(alternative_path));
    }

    height = texture->GetHeight();
    width = texture->GetWidth();

    // Posicion del listado de armas
    x = (SCREEN_WIDTH - texture->GetWidth()) / 2; 
    y = 0; 
}

void WeaponSelector::render(SDL2pp::Renderer& renderer) {
    // Agrego un rectangulo blanco detras para que quede como un borde alrededor del listado
    int border_width = 4;
    SDL_Color border_color = {255, 255, 255, 255}; 
    // Render del rectangulo / borde blanco
    renderer.SetDrawColor(border_color.r, border_color.g, border_color.b, border_color.a);
    renderer.FillRect(SDL2pp::Rect(x - border_width, y - border_width, width + 2 * border_width, height + 2 * border_width));  

    // Render del listado de armas
    renderer.Copy(*texture, SDL2pp::NullOpt, SDL2pp::Rect(x, y, width, height)); 

}

bool WeaponSelector::mouse_inside(int mouse_x, int mouse_y) { 
    int sprite_x = x;
    int sprite_y = y;

    bool inside_x = ( (mouse_x >= sprite_x)  && (mouse_x <= sprite_x + width) );
    bool inside_y = ( (mouse_y >= sprite_y)  && (mouse_y <= sprite_y + height) );
    
    return inside_x && inside_y;
}

int WeaponSelector::get_weapon_index(int mouse_x, int mouse_y) {
    int sprite_x = x;
    int sprite_y = y;
    
    int num_weapons = texture->GetWidth() / texture->GetHeight();
    double width_per_weapon = texture->GetWidth() / num_weapons;

    int mouse_position = mouse_x - sprite_x;

    int weapon_index = mouse_position / width_per_weapon;

    return weapon_index;
}
