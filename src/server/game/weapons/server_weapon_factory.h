//
// Created by xguss on 26/11/23.
//

#ifndef WORMS_SERVER_WEAPON_FACTORY_H
#define WORMS_SERVER_WEAPON_FACTORY_H

#include <map>
#include <memory>
#include <string>

#include "server_weapon.h"

class WeaponFactory {
public:
    static std::map<uint8_t, std::unique_ptr<Weapon>> get_weapons(GameWorld& world);
};

#endif  // WORMS_SERVER_WEAPON_FACTORY_H
