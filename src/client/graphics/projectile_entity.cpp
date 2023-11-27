
#include "projectile_entity.h"

#include "game/projectile.h"

projectileEntity::projectileEntity(TextureController& controller):
        texture_controller(controller),
        an(texture_controller.get_texture(AnimationState::IDLE), texture_controller),
        type(0),
        x(300),
        y(300) {}

projectileEntity::~projectileEntity() {}

void projectileEntity::update_info(EntityInfo* info) {
    auto projectile = dynamic_cast<Projectile*>(info);  // feo?

    x = projectile->get_pos_x();
    y = -projectile->get_pos_y();

    type = projectile->type;

    an.change_texture(projectile_controller.get_projectile_texture(type));
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void projectileEntity::update(float dt) { an.update(dt); }

void projectileEntity::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    an.render(renderer,
              SDL2pp::Rect(x * SCREEN_WIDTH / 20 - 25, y * SCREEN_HEIGHT / 20 - 25, 50, 50), flip);
}
