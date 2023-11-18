#include "weapon.h"
#include "bazooka.h"

#include <memory>

enum Weapons {
    BAZOOKA = 1,
};

class WeaponFactory {
public:
    std::unique_ptr<Weapon> create_weapon(uint8_t id);
};
