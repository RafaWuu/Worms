#include "player.h"
#include <iterator>

#include "../game/worm.h"

Player::Player(TextureController& controller, int id):
        texture_controller(controller),
        an(texture_controller.get_texture(AnimationState::BAZOOKA_IDLE), texture_controller),
        facingLeft(false),
        moving(false),
        jumping(false),
        rolling(false),
        aiming(false),
        falling(false),
        dead(false),
        x(300),
        y(300),
        id(id),
        config(Configuration::get_instance()) {
    crosshair = nullptr;
    hud = nullptr;
    current_weapon = std::make_unique<Bazooka>();
    health = 100;
}

void Player::add_crosshair() {
    crosshair = std::make_unique<Crosshair> (texture_controller.get_texture(AnimationState::CROSSHAIR), texture_controller);
}

Player::~Player() {}

void Player::update_info(EntityInfo* info, SoundController& sound_controller) {
    auto worm = dynamic_cast<Worm*>(info);  // feo?

    health = worm->get_health();

    x = worm->get_pos_x();
    y = worm->get_pos_y();
    //TODO actualizar si es mi gusano, reubicar
    // hud->update_ammo(worm->get_id(),worm->get_ammo());
    height = worm->get_height();
    width = worm->get_width();
    uint8_t dir = worm->get_dir();
    uint16_t new_state = worm->get_state();
    aim_angle = worm->get_aim_angle();

    current_weapon = weapon_factory.create_weapon(worm->get_current_weapon());

    // Hay que cambiar la textura si empieza a moverse o para de moverse
    bool is_moving_now = (new_state & 0x0004) ? true : false;
    bool is_jumping_now = (new_state & 0x0008) != 0;
    bool is_rolling_now = (new_state & 0x0010) != 0;
    bool is_aiming_now = (new_state & 0x0080) != 0;
    bool is_falling_now = (new_state & 0x0020) != 0;
    bool is_idle_now = ((new_state & 0x0002) != 0) || new_state == 1;
    bool is_dead_now = !(new_state & 0x0001);
    
    bool stopped_moving = moving && !is_moving_now;
    bool just_died = !dead && is_dead_now;
  
    if (stopped_moving) 
        sound_controller.stop_sound();
    if (just_died) 
        sound_controller.play_sound(DEATH);

    if (!moving && is_moving_now) {
        an.change_texture(WALKING);
    } else if (!jumping && is_jumping_now) {
        sound_controller.play_sound(JUMP);
        an.change_texture(JUMPING);
    } else if (!rolling && is_rolling_now) {
        sound_controller.play_sound(JUMP);
        an.change_texture(ROLLING);
    } else if (!falling && is_falling_now) {
        an.change_texture(FALLING);
    } else if (just_died) {
        an.change_texture(DEAD);
    } else if (!aiming && is_aiming_now) {
        an.change_texture(current_weapon->get_aiming_texture_state());
    } else if (is_idle_now && !is_aiming_now && !is_dead_now) {  
        an.change_texture(current_weapon->get_idle_texture_state());
    }

    moving = is_moving_now;
    jumping = is_jumping_now;
    rolling = is_rolling_now;
    aiming = is_aiming_now;
    falling = is_falling_now;
    dead = is_dead_now;
    idle = is_idle_now;

    if (moving) sound_controller.play_sound(WALK);

    if (dir == 1)
        facingLeft = false;
    if (dir == 0)
        facingLeft = true;
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
void Player::update(float dt) {
    if (!idle && !aiming) 
        an.update(dt);

    if (aiming) {
        if (facingLeft) {
            // Flippeo el angulo a la derecha
            if (aim_angle < 0)
                aim_angle = -(M_PI + aim_angle);
            else
                aim_angle = (M_PI - aim_angle);
        }
        an.update_by_angle(aim_angle);
    }
}

void Player::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    int offsetX = 1.58 * 25;
    int offsetY = -1.4 * 25;

    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    an.render(
            renderer,
            SDL2pp::Rect(x - width * 4 + offsetX, y - height * 4 - offsetY, width * 4, height * 4),
            flip);
    // render barra de vida 50x10
    int bar_width = (health * 50) / 100.0;
    SDL2pp::Rect health_bar = {x - 25, y - 55, bar_width, 10};
    renderer.SetDrawColor(color.r, color.g, color.b, color.a);
    renderer.FillRect(health_bar);

    if (aiming && crosshair) {
        crosshair->render_crosshair(renderer, x, y, aim_angle);
    }
}

uint16_t Player::get_id() const { return id; }
void Player::set_color(SDL2pp::Color color) { color = color; }
void Player::set_hud(std::shared_ptr<Hud> hud){hud = hud;}
