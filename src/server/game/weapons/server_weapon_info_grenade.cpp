//
// Created by xguss on 26/11/23.
//

#include "server_weapon_info_grenade.h"

#include "common_weapon_constants.h"

GrenadeWeaponInfo::GrenadeWeaponInfo(const GrenadeWeapon& grenade) {
    ammo = grenade.ammo;
    angle = grenade.aim_angle;
    power = grenade.aim_power;
    countdown = grenade.countdown;
}

void GrenadeWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(GREEN_GRENADE_ID);
    bp.send_2byte_number(ammo);
    bp.send_4byte_float(angle);
    bp.send_1byte_number(power * 255);
    bp.send_4byte_float(countdown);
}
