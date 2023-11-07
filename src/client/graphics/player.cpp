#include "player.h"
#include "../game/worm.h"

Player::Player(TextureController& controller, int id): texture_controller(controller), an(texture_controller.get_walking_sprite()), facingLeft(false), moving(false), x(300), y(300), id(id) {}

Player::~Player() {}

void Player::update_info(Worm& worm) {
    moving = true;
    health = worm.get_health();

    x = (worm.get_pos_x() * 320 / 20) + 320;
    y = (-worm.get_pos_y() * 240 / 20) + 240;

    int state = worm.get_state();
    if (state == WORM_STATE::Stop) moving = false;
    else if (state == WORM_STATE::Left) facingLeft = true;
    else if (state == WORM_STATE::Right) facingLeft = false;
}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util. 
 */
void Player::update(float dt) {
    if (moving) {
        an.update(dt);
    }
}

void Player::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    an.render(renderer, SDL2pp::Rect(x, y, 100, 100), flip);
}

void Player::moveRigth() {
    moving = true;
    facingLeft = false;
}

void Player::moveLeft() {
    moving = true;
    facingLeft = true;
}

void Player::stopMoving() {
    moving = false;
}

int Player::get_id() const {
    return id;
}