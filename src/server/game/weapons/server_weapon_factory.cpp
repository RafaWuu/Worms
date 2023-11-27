//
// Created by xguss on 26/11/23.
//

#include "server_weapon_factory.h"

#include <map>
#include <string>

#include "game/world/server_gameworld.h"

#include "common_weapon_constants.h"
#include "server_weapon_bazooka.h"
#include "server_weapon_grenade.h"
#include "server_weapon_mortar.h"
#include "server_weapon_redgrenade.h"

std::map<uint8_t, std::unique_ptr<Weapon>> WeaponFactory::get_weapons(GameWorld& world) {
    std::map<uint8_t, std::unique_ptr<Weapon>> weapons;

    weapons.emplace(BAZOOKA_ID, std::make_unique<BazookaWeapon>(world));
    weapons.emplace(MORTAR_ID, std::make_unique<MortarWeapon>(world));
    weapons.emplace(GREEN_GRENADE_ID, std::make_unique<GrenadeWeapon>(world));
    weapons.emplace(RED_GRENADE_ID, std::make_unique<RedGrenadeWeapon>(world));

    return weapons;
}
