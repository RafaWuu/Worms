#include "player.h"

#include "../game/worm.h"

Player::Player(TextureController& controller, int id):
        texture_controller(controller),
        an(texture_controller.get_texture(AnimationState::IDLE), texture_controller),
        facingLeft(false),
        moving(false),
        jumping(false),
        rolling(false),
        x(300),
        y(300),
        id(id) {}

Player::~Player() {}

void Player::update_info(EntityInfo* info) {
    auto worm = dynamic_cast<Worm*>(info);  // feo?

    health = worm->get_health();

    x = (worm->get_pos_x() * 640 / 20);
    y = (-worm->get_pos_y() * 480 / 20 + 480);

    uint8_t dir = worm->get_dir();
    uint16_t new_state = worm->get_state();

    // Hay que cambiar la textura si empieza a moverse o para de moverse
    bool is_moving_now = (new_state & 0x0004) ? true : false;
    bool is_jumping_now = (new_state & 0x0008) != 0;
    bool is_rolling_now = (new_state & 0x0010) != 0;

    if (!moving && is_moving_now) {
        an.change_texture(AnimationState::WALK);
    } else if (!jumping && is_jumping_now) {
        an.change_texture(AnimationState::JUMPING);
    } else if (!rolling && is_rolling_now) {
        an.change_texture(AnimationState::ROLLING);
    } else if ((moving && !is_moving_now) || (jumping && !is_jumping_now) ||
               (rolling && !is_rolling_now)) {
        an.change_texture(AnimationState::IDLE);
    }

    moving = is_moving_now;
    jumping = is_jumping_now;
    rolling = is_rolling_now;

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
    if (moving || rolling || jumping)
        an.update(dt);
}

void Player::render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    an.render(renderer, SDL2pp::Rect(x, y, 100, 100), flip);
}

uint16_t Player::get_id() const { return id; }