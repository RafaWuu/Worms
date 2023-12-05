

#ifndef WORMS_SERVER_WEAPON_BAT_H
#define WORMS_SERVER_WEAPON_BAT_H

#include <memory>

#include "server_weapon.h"


class WeaponBat: public Weapon {
private:
    float aim_angle;
    float aim_power;
    uint16_t worm_id;

public:
    friend class BatWeaponInfo;
    WeaponBat(GameWorld& world, uint16_t worm_id);
    bool aim_projectile(b2Body& body, float x, float y, bool facing_right) override;

    bool power_projectile() override;

    bool fire_projectile(b2Body& body, bool facing_right) override;

    std::unique_ptr<WeaponInfo> get_info() const override;
};

#endif  // WORMS_SERVER_WEAPON_BAT_H
