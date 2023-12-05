//
// Created by xguss on 11/11/23.
//

#include "server_weapon.h"

#include "../world/server_gameworld.h"

Weapon::Weapon(GameWorld& world): world(world), config(Configuration::get_instance()) {
    ammo = INFINITE_AMMO;
}

bool Weapon::adjust_projectile_countdown(float seconds) { return false; }

bool Weapon::power_projectile() { return false; }

bool Weapon::aim_projectile(b2Body& body, float x, float y, bool facing_right) { return false; }

void Weapon::add_ammo(int quantity) {
    if (ammo != INFINITE_AMMO)
        ammo += quantity;
}
