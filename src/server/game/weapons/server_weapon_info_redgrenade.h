

#ifndef WORMS_SERVER_WEAPON_INFO_REDGRENADE_H
#define WORMS_SERVER_WEAPON_INFO_REDGRENADE_H

#include "server_weapon_info.h"
#include "server_weapon_redgrenade.h"

class RedGrenadeWeaponInfo: public WeaponInfo {
private:
    float angle;
    float power;
    int ammo;
    float countdown;

public:
    explicit RedGrenadeWeaponInfo(const RedGrenadeWeapon& grenade);
    void serialize_status(BaseProtocol& bp) override;
};

#endif  // WORMS_SERVER_WEAPON_INFO_REDGRENADE_H
