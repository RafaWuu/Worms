

#ifndef WORMS_SERVER_WEAPON_INFO_BANANA_H
#define WORMS_SERVER_WEAPON_INFO_BANANA_H

#include "server_weapon_banana.h"
#include "server_weapon_info.h"

class BananaWeaponInfo: public WeaponInfo {
private:
    float angle;
    float power;
    int ammo;
    float countdown;

public:
    explicit BananaWeaponInfo(const BananaWeapon& grenade);
    void serialize_status(BaseProtocol& bp) override;
};

#endif  // WORMS_SERVER_WEAPON_INFO_BANANA_H
