#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include <memory>

#include "../../../common/common_weapon_constants.h"
#include "../../configuration/configuration.h"
#include "../client/client_client.h"

#include "bazooka.h"
#include "weapon.h"

class WeaponFactory {
public:
    std::unique_ptr<Weapon> create_weapon(uint8_t id);
};

#endif