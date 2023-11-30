//
// Created by xguss on 30/11/23.
//

#include "server_weapon_info_teleportation.h"

#include "common_weapon_constants.h"


TeleportationWeaponInfo::TeleportationWeaponInfo(const TeleportationWeapon& object) {
    aim_x = object.aim_x;
    aim_y = object.aim_y;
    ammo = object.ammo;
}

void TeleportationWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(TELEPORTATION_ID);
    bp.send_2byte_number(ammo);
    bp.send_4byte_float(aim_x);
    bp.send_4byte_float(aim_y);
}
