

#include "server_weapon_factory.h"

#include <map>
#include <string>

#include "game/world/server_gameworld.h"

#include "common_weapon_constants.h"
#include "server_weapon_airattack.h"
#include "server_weapon_banana.h"
#include "server_weapon_bat.h"
#include "server_weapon_bazooka.h"
#include "server_weapon_dynamite.h"
#include "server_weapon_grenade.h"
#include "server_weapon_holygrenade.h"
#include "server_weapon_mortar.h"
#include "server_weapon_redgrenade.h"
#include "server_weapon_teleportation.h"

std::map<uint8_t, std::unique_ptr<Weapon>> WeaponFactory::get_weapons(GameWorld& world,
                                                                      Worm& worm) {
    std::map<uint8_t, std::unique_ptr<Weapon>> weapons;

    weapons.emplace(BAZOOKA_ID, std::make_unique<BazookaWeapon>(world));
    weapons.emplace(MORTAR_ID, std::make_unique<MortarWeapon>(world));
    weapons.emplace(GREEN_GRENADE_ID, std::make_unique<GrenadeWeapon>(world));
    weapons.emplace(RED_GRENADE_ID, std::make_unique<RedGrenadeWeapon>(world));
    weapons.emplace(BANANA_ID, std::make_unique<BananaWeapon>(world));
    weapons.emplace(HOLY_GRENADE_ID, std::make_unique<HolyGrenadeWeapon>(world));
    weapons.emplace(DYNAMITE_ID, std::make_unique<DynamiteWeapon>(world));
    weapons.emplace(BASEBALL_BAT_ID, std::make_unique<WeaponBat>(world, worm.id));
    weapons.emplace(TELEPORTATION_ID, std::make_unique<TeleportationWeapon>(world));
    weapons.emplace(AIR_ATTACK_ID, std::make_unique<AirAttackWeapon>(world));

    return weapons;
}
