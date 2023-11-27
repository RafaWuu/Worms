//
// Created by xguss on 26/11/23.
//

#include "server_weapon_mortar_info.h"

#include "common_weapon_constants.h"

MortarWeaponInfo::MortarWeaponInfo(const MortarWeapon& mortar) {
    ammo = mortar.ammo;
    angle = mortar.aim_angle;
    power = mortar.aim_power;
}

void MortarWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(MORTAR_ID);
    bp.send_2byte_number(ammo);
    bp.send_4byte_float(angle);
    bp.send_1byte_number(power * 255);
}
