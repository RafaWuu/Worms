#include "player.h"

#include "../game/worm.h"

Player::Player(TextureController& controller, int id):
        texture_controller(controller),
        an(texture_controller.get_texture(AnimationState::BAZOOKA_IDLE), texture_controller),
        crosshair(texture_controller.get_texture(AnimationState::CROSSHAIR), texture_controller),
        facingLeft(false),
        moving(false),
        jumping(false),
        rolling(false),
        aiming(false),
        falling(false),
        dead(false),
        x(300),
        y(300),
        id(id) {
    current_weapon = std::make_unique<Bazooka>();
    health = 100;
}

Player::~Player() {}

void Player::update_info(EntityInfo* info) {
    auto worm = dynamic_cast<Worm*>(info);  // feo?

    health = worm->get_health();

    x = worm->get_pos_x() * SCREEN_WIDTH / 20;
    y = -worm->get_pos_y() * SCREEN_HEIGHT / 20;

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
    bool is_idle_now = (new_state & 0x0002) != 0;
    bool is_dead_now = !health;
    
    // TODO: cambiar textura cuando apunta y elegir frame segun el angulo
    
    if (!moving && is_moving_now) {
        an.change_texture(WALKING);
    } else if (!jumping && is_jumping_now) {
        an.change_texture(JUMPING);
    } else if (!rolling && is_rolling_now) {
        an.change_texture(ROLLING);
    } else if (!falling && is_falling_now) {
        an.change_texture(FALLING);
    } else if (!dead && is_dead_now) {
        an.change_texture(DEAD);
    } else if (!idle && is_idle_now) {
        an.change_texture(current_weapon->get_idle_texture_state());
    }

    moving = is_moving_now;
    jumping = is_jumping_now;
    rolling = is_rolling_now;
    aiming = is_aiming_now;
    falling = is_falling_now;
    dead = is_dead_now;
    idle = is_idle_now;

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
    // El frame del aiming se debe elegir segun el angulo
    if (!idle && !aiming) 
        an.update(dt);
}

void Player::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {

    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    an.render(renderer, SDL2pp::Rect(x - 50, y - 50, 100, 100), flip);
    // render barra de vida 50x10
    int bar_width = (health * 50) / 100.0;
    SDL2pp::Rect health_bar = {x - 25, y - 55, bar_width, 10};
    renderer.SetDrawColor(color.r, color.g, color.b, color.a);
    renderer.FillRect(health_bar);

    if (aiming) {
        crosshair.render_crosshair(renderer, x, y, aim_angle);
    }
}

uint16_t Player::get_id() const { return id; }
void Player::set_color(SDL2pp::Color color) { color = color; }
