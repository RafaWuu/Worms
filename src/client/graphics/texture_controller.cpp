#include "texture_controller.h"

#include <string>
#include <utility>

static Uint32 get_color_key(uint8_t r, uint8_t g, uint8_t b);

TextureController::TextureController(SDL2pp::Renderer& renderer_): renderer(renderer_) {
    Uint32 blue_color_key = get_color_key(0x80, 0x80, 0xC0);

    std::map<AnimationState, std::string> textures_to_load = {
        {AnimationState::WALKING, "wwalk2.png"},
        {AnimationState::IDLE, "wblink1.png"},
        {AnimationState::JUMPING, "wjumpd.png"},
        {AnimationState::ROLLING, "wbackflp.png"},
        {AnimationState::SCENARIO_BEAM_3M, "beam_3m.png"},
        {AnimationState::SCENARIO_BEAM_6M, "beam_6m.png"},
        //{AnimationState::SCENARIO_GROUND, "blue00.bmp"},
        {AnimationState::BAZOOKA_IDLE, "wbazbak.png"}, // Quiza usar el mismo sprite para idle/aiming?
        {AnimationState::BAZOOKA_AIMING, "wbaz.png"},
        {AnimationState::CROSSHAIR, "crshairr.png"},
        {AnimationState::SCENARIO_BACKGROUND, "background.png"},
    };

    for (auto const& texture: textures_to_load) {
        load_texture(texture.first, texture.second, blue_color_key);
    }
}

std::shared_ptr<SDL2pp::Texture> TextureController::get_texture(AnimationState state) {
    return textures[state];
}

// Color del pixel que hay que hacer transparente
static Uint32 get_color_key(uint8_t r, uint8_t g, uint8_t b) {
    // Medio feo lo del alternative_path, seguro hay una manera mejor de hacerlo
    std::string path = "../assets/wwalk2.png";
    std::string alternative_path = "assets/wwalk2.png";

    try {
        SDL2pp::Surface surface(path);
        Uint32 color_key = SDL_MapRGB(surface.Get()->format, r, g, b);
        return color_key;
    } catch (SDL2pp::Exception& e) {
        SDL2pp::Surface surface(alternative_path);
        Uint32 color_key = SDL_MapRGB(surface.Get()->format, r, g, b);
        return color_key;
    }
}

void TextureController::load_texture(AnimationState state, const std::string& file_name,
                                     Uint32 color_key) {
    std::string path = "../assets/" + file_name;
    std::string alternative_path = "assets/" + file_name;

    try {
        SDL2pp::Texture texture(renderer, SDL2pp::Surface(path).SetColorKey(true, color_key));
        textures.emplace(state, std::make_shared<SDL2pp::Texture>(std::move(texture)));
    } catch (SDL2pp::Exception& e) {
        SDL2pp::Texture texture(renderer,
                                SDL2pp::Surface(alternative_path).SetColorKey(true, color_key));
        textures.emplace(state, std::make_shared<SDL2pp::Texture>(std::move(texture)));
    }
}
