#include "worm.h"

#include "graphics/player.h"

Worm::Worm(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height,
           uint8_t dir, uint16_t state, uint8_t health, uint8_t current_weapon, int ammo,
           uint8_t attack_power, AimInfo aim_info):
        dir(dir),
        id(id),
        state(state),
        health(health),
        current_weapon(current_weapon),
        ammo(ammo),
        attack_power(attack_power),
        aim_info(aim_info),
        EntityInfo(pos_x, pos_y, width, height) {}

Worm::Worm(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height,
           uint8_t dir, uint16_t state, uint8_t health, uint8_t current_weapon):
        dir(dir),
        id(id),
        state(state),
        health(health),
        current_weapon(current_weapon),
        ammo(0),
        attack_power(0),
        aim_info(0, 0, 0, COORDINATES),
        EntityInfo(pos_x, pos_y, width, height) {}

int Worm::get_health() { return health; }

int Worm::get_state() { return state; }

uint16_t Worm::get_id() const { return id; }

uint8_t Worm::get_dir() const { return dir; }

uint8_t Worm::get_current_weapon() { return current_weapon; }

int Worm::get_ammo() { return ammo; }

float Worm::get_aim_angle() { return aim_info.get_angle(); }
float Worm::get_x_aim() { return aim_info.get_x(); }
float Worm::get_y_aim() { return aim_info.get_y(); }
AimInfo Worm::get_aim_info() { return aim_info; }

uint8_t Worm::get_attack_power() { return attack_power; }

std::unique_ptr<Entity> Worm::create(TextureController& controller) {
    return std::make_unique<Player>(controller, get_id());
}
