#include "worm.h"

#include "graphics/player.h"

Worm::Worm(uint16_t id, float pos_x, float pos_y, uint8_t dir, uint16_t state, uint8_t vida):
        dir(dir), id(id), pos_x(pos_x), pos_y(pos_y), state(state), health(vida) {}

float Worm::get_pos_x() const { return pos_x; }

float Worm::get_pos_y() const { return pos_y; }

int Worm::get_health() { return health; }

int Worm::get_state() { return state; }

uint16_t Worm::get_id() const { return id; }

uint8_t Worm::get_dir() const { return dir; }

std::unique_ptr<Entity> Worm::create(TextureController& controller) {
    return std::make_unique<Player>(controller, get_id());
}
