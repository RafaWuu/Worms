//
// Created by xguss on 30/11/23.
//

#ifndef WORMS_SERVER_WEAPON_TELEPORTATION_H
#define WORMS_SERVER_WEAPON_TELEPORTATION_H

#include "server_weapon.h"

class TeleportationWeapon: public Weapon {
private:
    int ammo;
    float aim_x;
    float aim_y;

public:
    friend class TeleportationWeaponInfo;
    explicit TeleportationWeapon(GameWorld& world);
    bool aim_projectile(b2Body& body, float x, float y, bool facing_right) override;
    bool fire_projectile(b2Body& body, bool facing_right) override;
    std::unique_ptr<WeaponInfo> get_info() const override;
};

#endif  // WORMS_SERVER_WEAPON_TELEPORTATION_H
