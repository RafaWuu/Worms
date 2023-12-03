#include "explosion_entity.h"
#include <iostream>
#include <ostream>

#include "game/explosion.h"

ExplosionEntity::ExplosionEntity(TextureController& controller, uint8_t type, float radius):
        texture_controller(controller),
        circle(texture_controller.get_texture(EXPLOSION_CIRCLE), texture_controller),
        elipse(texture_controller.get_texture(EXPLOSION_ELIPSE), texture_controller),
        type(0),
        x(300),
        y(300),
        radius(radius),
        just_exploded(true),
        frames_rendered(0),
        config(Configuration::get_instance()) {}

ExplosionEntity::~ExplosionEntity() {}

void ExplosionEntity::update_info(EntityInfo* info, SoundController& sound_controller) {
    auto explosion = dynamic_cast<Explosion*>(info);  // feo?

    x = explosion->get_pos_x();
    y = explosion->get_pos_y();

    if (just_exploded) {
        sound_controller.play_sound(EXPLOSION);
        just_exploded = false;
    }
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void ExplosionEntity::update(float dt) {
    
    circle.update(dt);
    elipse.update(dt);

}

void ExplosionEntity::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    
    if (frames_rendered >= circle.get_num_frames()) {
        return;
    }

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    circle.render(renderer, SDL2pp::Rect(x - radius, y - radius, radius * 2, radius * 2), flip,
                  0.0);

    elipse.render(renderer, SDL2pp::Rect(x - radius, y - radius, radius * 2, radius * 2), flip,
                  0.0);
    
    frames_rendered++;
}
