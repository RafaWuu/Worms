//
// Created by xguss on 27/11/23.
//

#ifndef WORMS_SERVER_WEAPON_INFO_HOLYGRENADE_H
#define WORMS_SERVER_WEAPON_INFO_HOLYGRENADE_H

#include "server_weapon_holygrenade.h"
#include "server_weapon_info.h"

class HolyGrenadeWeaponInfo: public WeaponInfo {
private:
    float angle;
    float power;
    int ammo;
    float countdown;

public:
    explicit HolyGrenadeWeaponInfo(const HolyGrenadeWeapon& grenade);
    void serialize_status(BaseProtocol& bp) override;
};

#endif  // WORMS_SERVER_WEAPON_INFO_HOLYGRENADE_H
