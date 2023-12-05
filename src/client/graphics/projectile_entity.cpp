
#include "projectile_entity.h"

#include "game/projectile.h"

projectileEntity::projectileEntity(TextureController& controller, uint8_t type):
        texture_controller(controller),
        an(texture_controller.get_texture(IDLE), texture_controller),
        type(0),
        x(300),
        y(300),
        config(Configuration::get_instance()),
        was_just_thrown(true) {

    weapon = weapon_factory.create_weapon(type);

    an.change_texture(weapon->get_projectile_texture());
}

projectileEntity::~projectileEntity() {}

void projectileEntity::update_info(EntityInfo* info, SoundController& sound_controller) {
    auto projectile = dynamic_cast<Projectile*>(info);  // feo?

    x = projectile->get_pos_x();
    y = projectile->get_pos_y();
    width = projectile->get_width();
    height = projectile->get_height();
    angle = projectile->get_angle();

    auto type_s = config.get_weapon_name(type);

    if (was_just_thrown) {
        sound_controller.play_sound(THROW);
        was_just_thrown = false;
    }
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void projectileEntity::update(float dt) { 
    // Proyectiles que no tienen "breathing" effect
    if (!weapon->projectile_should_loop()) 
        return;

    an.update(dt); 
}

void projectileEntity::render(SDL2pp::Renderer& renderer, Camera& camera) {
    float angle_degrees = angle * (180.0f / M_PI) + 90.0f;

    int offsetX = -1 * 25;
    int offsetY = -.5 * 25;

    float rotation = (weapon->projectile_should_loop()) ? 0 : angle_degrees;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    an.render(
            renderer,
            SDL2pp::Rect(x - camera.get_x() - width / 2 + offsetX, y - camera.get_y() - height / 2 + offsetY, width * 4, height * 4),
            flip, rotation);
}
