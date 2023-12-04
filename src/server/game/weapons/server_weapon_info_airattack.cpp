//
// Created by xguss on 03/12/23.
//

#include "server_weapon_info_airattack.h"

#include "common_weapon_constants.h"

AirAttackWeaponInfo::AirAttackWeaponInfo(const AirAttackWeapon& object) {
    aim_x = object.aim_x;
    aim_y = object.aim_y;
    ammo = object.ammo;
}

void AirAttackWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(AIR_ATTACK_ID);
    bp.send_2byte_number(ammo);
    bp.send_4byte_float(aim_x);
    bp.send_4byte_float(aim_y);
}