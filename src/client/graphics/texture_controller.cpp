#include "texture_controller.h"

#include <string>
#include <utility>

static Uint32 get_color_key(uint8_t r, uint8_t g, uint8_t b);

TextureController::TextureController(SDL2pp::Renderer& renderer_): renderer(renderer_) {
    Uint32 light_blue_color_key = get_color_key(0x80, 0x80, 0xC0);
    Uint32 dark_blue_color_key = get_color_key(32, 32, 248);
    Uint32 yellow_color_key = get_color_key(192, 192, 128);

    std::map<AnimationState, std::string> textures_light_blue_bg = {
            {WALKING, "wwalk2.png"},
            {IDLE, "wblink1.png"},
            {JUMPING, "wjumpd.png"},
            {ROLLING, "wbackflp.png"},
            {FALLING, "wfall.png"},
            {DEAD, "grave2.png"},
            {SCENARIO_BEAM_3M, "beam_3m.png"},
            {SCENARIO_BEAM_6M, "beam_6m.png"},
            //{AnimationState::SCENARIO_GROUND, "blue00.bmp"},
            {BAZOOKA_IDLE, "wbazbak.png"},  // Quiza usar el mismo sprite para idle/aiming?
            {BAZOOKA_AIMING, "wbaz.png"},
            {BAZOOKA_PROJECTILE, "missile.png"},
            {MORTAR_IDLE, "wbazbak.png"},
            {MORTAR_AIMING, "wbaz.png"},
            {CROSSHAIR, "crshairr.png"},
            {SCENARIO_BACKGROUND, "background.png"},
            {RED_GRENADE_IDLE, "wclsbak.png"},
            {RED_GRENADE_AIMING, "wthrcls.png"},
            {RED_GRENADE_PROJECTILE, "cluster.png"},
            {GREEN_GRENADE_IDLE, "wgrnbak.png"},
            {GREEN_GRENADE_AIMING, "wthrgrn.png"},
            {GREEN_GRENADE_PROJECTILE, "grenade.png"},
            {HOLY_GRENADE_IDLE, "whgrbak.png"},
            {HOLY_GRENADE_AIMING, "wthrhgr.png"},
            {HOLY_GRENADE_PROJECTILE, "hgrenade.png"},
            {BANANA_IDLE, "wbanbak.png"},
            {BANANA_AIMING, "wthrban.png"},
            {BANANA_PROJECTILE, "banana.png"},
            {DYNAMITE_IDLE, "wdynbak.png"},
            {DYNAMITE_AIMING, "wdynbak.png"},
            {DYNAMITE_PROJECTILE, "dynamite.png"},
            {EXPLOSION_CIRCLE, "circle50.png"},
    };

    std::map<AnimationState, std::string> textures_yellow_bg = {
            {MORTAR_PROJECTILE, "mortar.png"},     {BAT_IDLE, "wbsbbak.png"},
            {BAT_AIMING, "wbsbaim.png"}, {TELEPORTATION_IDLE, "wtelbak.png"},
            {TELEPORTATION_AIMING, "teleportation.png"},
    };

    std::map<AnimationState, std::string> textures_dark_blue_bg = {
        {EXPLOSION_ELIPSE, "elipse50.png"},
    };

    for (auto const& texture: textures_light_blue_bg) {
        load_texture(texture.first, texture.second, light_blue_color_key);
    }

    for (auto const& texture: textures_yellow_bg) {
        load_texture(texture.first, texture.second, yellow_color_key);
    }

    for (auto const& texture: textures_dark_blue_bg) {
        load_texture(texture.first, texture.second, dark_blue_color_key);
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
