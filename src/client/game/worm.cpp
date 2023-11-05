#include "worm.h"

Worm::Worm(int8_t id, float pos_x, float pos_y, int8_t state, int8_t vida):
        id(id), pos_x(pos_x), pos_y(pos_y), state(state), health(vida) {}

float Worm::get_pos_x() { return pos_x; }

float Worm::get_pos_y() { return pos_y; }
