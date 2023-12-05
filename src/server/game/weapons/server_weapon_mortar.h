//
// Created by xguss on 26/11/23.
//

#ifndef WORMS_SERVER_WEAPON_MORTAR_H
#define WORMS_SERVER_WEAPON_MORTAR_H

#include <memory>

#include "game/world/server_gameworld.h"

#include "server_weapon.h"

class MortarWeapon: public Weapon {
private:
    float aim_angle;
    float aim_power;

public:
    friend class MortarWeaponInfo;

    explicit MortarWeapon(GameWorld& world);
    ~MortarWeapon() override = default;
    bool aim_projectile(b2Body& body, float x, float y, bool facing_right) override;

    bool power_projectile() override;

    bool fire_projectile(b2Body& body, bool facing_right) override;

    std::unique_ptr<WeaponInfo> get_info() const override;
};

#endif  // WORMS_SERVER_WEAPON_MORTAR_H
