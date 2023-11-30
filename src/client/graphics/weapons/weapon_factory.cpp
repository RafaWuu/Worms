#include "weapon_factory.h"

#include "teleportation.h"

std::unique_ptr<Weapon> WeaponFactory::create_weapon(uint8_t weapon_id) {
    if (weapon_id == BAZOOKA_ID)
        return std::make_unique<Bazooka>();
    if (weapon_id == GREEN_GRENADE_ID)
        return std::make_unique<GreenGrenade>();
    if (weapon_id == RED_GRENADE_ID)
        return std::make_unique<RedGrenade>();
    if (weapon_id == HOLY_GRENADE_ID)
        return std::make_unique<HolyGrenade>();
    if (weapon_id == MORTAR_ID)
        return std::make_unique<Mortar>();
    if (weapon_id == BANANA_ID)
        return std::make_unique<Banana>();
    if (weapon_id == DYNAMITE_ID)
        return std::make_unique<Dynamite>();
    if (weapon_id == BASEBALL_BAT_ID)
        return std::make_unique<BaseballBat>();
    if (weapon_id == TELEPORTATION_ID)
        return std::make_unique<Teleportation>();
    return std::make_unique<Bazooka>();
}