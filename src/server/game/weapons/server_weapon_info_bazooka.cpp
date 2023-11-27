//
// Created by xguss on 26/11/23.
//

#include "server_weapon_info_bazooka.h"

#include "common_weapon_constants.h"

BazookaWeaponInfo::BazookaWeaponInfo(const BazookaWeapon& bazooka) {
    ammo = bazooka.ammo;
    angle = bazooka.aim_angle;
    power = bazooka.aim_power;
}

void BazookaWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(BAZOOKA_ID);
    bp.send_2byte_number(ammo);
    bp.send_4byte_float(angle);
    bp.send_1byte_number(power * 255);
}
