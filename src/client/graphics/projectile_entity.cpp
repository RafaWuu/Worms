
#include "projectile_entity.h"

#include "game/projectile.h"

projectileEntity::projectileEntity(TextureController& controller):
        texture_controller(controller),
        an(texture_controller.get_texture(AnimationState::IDLE), texture_controller),
        type(0),
        x(300),
        y(300),
        config(Configuration::get_instance()) {}

projectileEntity::~projectileEntity() {}

void projectileEntity::update_info(EntityInfo* info) {
    auto projectile = dynamic_cast<Projectile*>(info);  // feo?

    x = projectile->get_pos_x();
    y = projectile->get_pos_y();
    width = projectile->get_width();
    height = projectile->get_height();
    angle = projectile->get_angle();

    type = projectile->type;
    auto type_s = config.get_weapon_name(type);

    an.change_texture(projectile_controller.get_projectile_texture(type));
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void projectileEntity::update(float dt) { an.update(dt); }

void projectileEntity::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    float angle_degrees = angle * (180.0f / M_PI);

    int offsetX = -1 * 25;
    int offsetY = -.5 * 25;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    an.render(
            renderer,
            SDL2pp::Rect(x - width / 2 + offsetX, y - height / 2 + offsetY, width * 4, height * 4),
            flip, angle_degrees);
}
