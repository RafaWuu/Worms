//
// Created by xguss on 27/11/23.
//

#ifndef WORMS_SERVER_WEAPON_DYNAMITE_H
#define WORMS_SERVER_WEAPON_DYNAMITE_H

#include <memory>

#include "server_weapon.h"

class DynamiteWeapon: public Weapon {
private:
    float countdown;
    int ammo;

public:
    friend class DynamiteWeaponInfo;
    explicit DynamiteWeapon(GameWorld& world);
    bool aim_projectile(b2Body& body, float x, float y, bool facing_right) override;

    bool power_projectile() override;

    bool fire_projectile(b2Body& body, bool facing_right) override;

    bool adjust_projectile_countdown(float seconds) override;
    std::unique_ptr<WeaponInfo> get_info() const override;
};

#endif  // WORMS_SERVER_WEAPON_DYNAMITE_H
