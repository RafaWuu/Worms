
#include "proyectil_entity.h"

#include "game/proyectil.h"

ProyectilEntity::ProyectilEntity(TextureController& controller):
        texture_controller(controller),
        an(texture_controller.get_texture(AnimationState::IDLE), texture_controller),
        type(0),
        x(300),
        y(300) {}

ProyectilEntity::~ProyectilEntity() {}

void ProyectilEntity::update_info(EntityInfo* info) {
    auto proyectil = dynamic_cast<Proyectil*>(info);  // feo?

    x = (proyectil->get_pos_x() * 640 / 20);
    y = (-proyectil->get_pos_y() * 480 / 20 + 480);

    type = proyectil->type;
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void ProyectilEntity::update(float dt) { an.update(dt); }

void ProyectilEntity::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    an.render(renderer, SDL2pp::Rect(x, y, 50, 50), flip);
}
