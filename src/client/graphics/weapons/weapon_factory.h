#include "weapon.h"
#include "bazooka.h"
#include "configuration/configuration.h"
#include "../../../common/common_weapon_constants.h"

#include <memory>

class WeaponFactory {
public:
    std::unique_ptr<Weapon> create_weapon(uint8_t id);
};
