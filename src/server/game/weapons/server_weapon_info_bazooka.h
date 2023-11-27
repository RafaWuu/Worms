//
// Created by xguss on 26/11/23.
//

#ifndef WORMS_SERVER_WEAPON_INFO_BAZOOKA_H
#define WORMS_SERVER_WEAPON_INFO_BAZOOKA_H

#include <memory>

#include "server_weapon_bazooka.h"
#include "server_weapon_info.h"

class BazookaWeaponInfo: public WeaponInfo {
private:
    float angle;
    float power;
    int ammo;

public:
    explicit BazookaWeaponInfo(const BazookaWeapon& bazooka);

    void serialize_status(BaseProtocol& bp) override;
};
#endif  // WORMS_SERVER_WEAPON_INFO_BAZOOKA_H
