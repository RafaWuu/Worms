//
// Created by xguss on 24/11/23.
//

#ifndef WORMS_SERVER_WEAPON_BAZOOKA_H
#define WORMS_SERVER_WEAPON_BAZOOKA_H

#include <memory>

#include "server_weapon.h"

class BazookaWeapon: public Weapon {
private:
    float aim_angle;
    float aim_power;
    int ammo;

public:
    friend class BazookaWeaponInfo;

    explicit BazookaWeapon(GameWorld& world);
    bool aim_projectile(b2Body& body, float x, float y, bool facing_right) override;

    bool power_projectile() override;

    bool fire_projectile(b2Body& body, bool facing_right) override;
    std::unique_ptr<WeaponInfo> get_info() const override;
};

#endif  // WORMS_SERVER_WEAPON_BAZOOKA_H
