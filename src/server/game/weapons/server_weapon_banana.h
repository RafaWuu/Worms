//
// Created by xguss on 27/11/23.
//

#ifndef WORMS_SERVER_WEAPON_BANANA_H
#define WORMS_SERVER_WEAPON_BANANA_H

#include <memory>

#include "server_weapon.h"

class BananaWeapon: public Weapon {
private:
    float countdown;
    float aim_angle;
    float aim_power;
    int ammo;

public:
    friend class BananaWeaponInfo;
    explicit BananaWeapon(GameWorld& world);
    bool aim_projectile(b2Body& body, float x, float y, bool facing_right) override;
    bool power_projectile() override;
    bool fire_projectile(b2Body& body, bool facing_right) override;
    bool adjust_projectile_countdown(float seconds) override;
    std::unique_ptr<WeaponInfo> get_info() const override;
};
#endif  // WORMS_SERVER_WEAPON_BANANA_H
