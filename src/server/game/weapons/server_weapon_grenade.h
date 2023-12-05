

#ifndef WORMS_SERVER_WEAPON_GRENADE_H
#define WORMS_SERVER_WEAPON_GRENADE_H

#include <memory>

#include "server_weapon.h"

class GrenadeWeapon: public Weapon {
private:
    float countdown;
    float aim_angle;
    float aim_power;

public:
    friend class GrenadeWeaponInfo;
    explicit GrenadeWeapon(GameWorld& world);
    bool aim_projectile(b2Body& body, float x, float y, bool facing_right) override;

    bool power_projectile() override;

    bool fire_projectile(b2Body& body, bool facing_right) override;

    bool adjust_projectile_countdown(float seconds) override;
    std::unique_ptr<WeaponInfo> get_info() const override;
};
#endif  // WORMS_SERVER_WEAPON_GRENADE_H
