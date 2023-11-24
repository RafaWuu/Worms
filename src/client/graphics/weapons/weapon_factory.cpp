#include "weapon_factory.h"

std::unique_ptr<Weapon> WeaponFactory::create_weapon(uint8_t weapon_id) {
    if (weapon_id == BAZOOKA_ID) return std::make_unique<Bazooka>();

    return std::make_unique<Bazooka>();
}