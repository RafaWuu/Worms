//
// Created by xguss on 30/11/23.
//

#ifndef WORMS_SERVER_WEAPON_INFO_BAT_H
#define WORMS_SERVER_WEAPON_INFO_BAT_H

#include "server_weapon_bat.h"
#include "server_weapon_info.h"

class BatWeaponInfo: public WeaponInfo {
private:
    float angle;
    float power;
    int ammo;

public:
    explicit BatWeaponInfo(const WeaponBat& bat);
    void serialize_status(BaseProtocol& bp) override;
};

#endif  // WORMS_SERVER_WEAPON_INFO_BAT_H
