//
// Created by xguss on 27/11/23.
//

#ifndef WORMS_SERVER_WEAPON_HOLYGRENADE_H
#define WORMS_SERVER_WEAPON_HOLYGRENADE_H

#include <memory>

#include "server_weapon.h"

class HolyGrenadeWeapon: public Weapon {
private:
    float countdown;
    float aim_angle;
    float aim_power;
    int ammo;

public:
    friend class HolyGrenadeWeaponInfo;
    explicit HolyGrenadeWeapon(GameWorld& world);
    bool aim_projectile(b2Body& body, float x, float y, bool facing_right) override;

    bool power_projectile() override;

    bool fire_projectile(b2Body& body, bool facing_right) override;

    bool adjust_projectile_countdown(float seconds) override;
    std::unique_ptr<WeaponInfo> get_info() const override;
};
#endif  // WORMS_SERVER_WEAPON_HOLYGRENADE_H
