//
// Created by xguss on 30/11/23.
//

#ifndef WORMS_SERVER_WEAPON_INFO_TELEPORTATION_H
#define WORMS_SERVER_WEAPON_INFO_TELEPORTATION_H

#include "server_weapon_info.h"
#include "server_weapon_teleportation.h"

class TeleportationWeaponInfo: public WeaponInfo {
private:
    float aim_x;
    float aim_y;

public:
    explicit TeleportationWeaponInfo(const TeleportationWeapon& object);
    void serialize_status(BaseProtocol& bp) override;
};

#endif  // WORMS_SERVER_WEAPON_INFO_TELEPORTATION_H
