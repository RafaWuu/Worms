#include "hud.h"
#include <memory>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/SDL.hh>

Hud::Hud(SDL2pp::Renderer& renderer, std::map<uint16_t, uint16_t> worms_distribution):
        renderer(renderer),
        worms_distribution(worms_distribution),
        ammo(0),
        time(0),
        offset(0),
        hp_map() {
    for (auto worm_client_id: worms_distribution) {
        hp_map[worm_client_id.second][worm_client_id.first] = 0;
    }
}

void Hud::update_hp(int worm_id, int hp) {
    auto client_id = worms_distribution[worm_id];
    hp_map[client_id][worm_id] = hp;
}
void Hud::update_time(int time) { time = time; }
void Hud::update_ammo(int worm_id, int ammo) {
    if (worm_id == current_worm) {
        ammo = ammo;
    }
}
void Hud::update_current_worm(int worm_id) { worm_id = current_worm; }

static std::unique_ptr<SDL2pp::Font> get_font() {
    try {
        std::string path = std::string(ASSETS_PATH)+"/Vera.ttf";
        return std::make_unique<SDL2pp::Font> (path, 12);
    } catch (SDL2pp::Exception& e) {
        std::cerr<<"Error font: "<<e.what()<<std::endl; 
        // return std::make_unique<SDL2pp::Font> ("../assets/Vera.ttf", 12);
    }
    
}

void Hud::render_hp() {
    // client_hp --> client_id:{worm_id:worm_hp,..,...}
    offset = 0;
    for (auto client_worm_id: hp_map) {
        int hp = 0;
        for (auto worm_id_hp: client_worm_id.second) {
            hp += worm_id_hp.second;
        }

        std::unique_ptr<SDL2pp::Font> font = get_font();
        std::string text =
                "Player " + std::to_string(client_worm_id.first) + ": " + std::to_string(hp);
        SDL2pp::Texture hp_sprite(renderer,
                                  font->RenderText_Blended(text, SDL2pp::Color{255, 0, 0, 255}));

        renderer.Copy(hp_sprite, SDL2pp::NullOpt,
                      SDL2pp::Rect(0, hp_sprite.GetHeight() * offset, hp_sprite.GetWidth(),
                                   hp_sprite.GetHeight()));
        offset++;
    }
}

void Hud::render_ammo() {
    std::unique_ptr<SDL2pp::Font> font = get_font();
    
    std::string text = "Ammo: " + std::to_string(0);
    SDL2pp::Texture ammo_sprite(renderer,
                                font->RenderText_Blended(text, SDL2pp::Color{255, 0, 0, 255}));

    renderer.Copy(ammo_sprite, SDL2pp::NullOpt,
                  SDL2pp::Rect(0, ammo_sprite.GetWidth() * offset, ammo_sprite.GetWidth(),
                               ammo_sprite.GetHeight()));
}

void Hud::render_timer() {}

void Hud::render() {
    render_hp();
    render_ammo();
    // render_timer();
}

Hud::~Hud() {}
