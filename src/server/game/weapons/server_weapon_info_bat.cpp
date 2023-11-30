//
// Created by xguss on 30/11/23.
//

#include "server_weapon_info_bat.h"

#include "common_weapon_constants.h"

BatWeaponInfo::BatWeaponInfo(const WeaponBat& bat) {
    ammo = bat.ammo;
    angle = bat.aim_angle;
    power = bat.aim_power;
}

void BatWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(BASEBALL_BAT_ID);
    bp.send_2byte_number(ammo);
    bp.send_4byte_float(angle);
}