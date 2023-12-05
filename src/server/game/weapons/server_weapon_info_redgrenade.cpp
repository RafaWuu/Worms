

#include "server_weapon_info_redgrenade.h"

#include <memory>

#include "common_weapon_constants.h"

RedGrenadeWeaponInfo::RedGrenadeWeaponInfo(const RedGrenadeWeapon& grenade) {
    ammo = grenade.ammo;
    angle = grenade.aim_angle;
    power = grenade.aim_power;
    countdown = grenade.countdown;
}

void RedGrenadeWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(RED_GRENADE_ID);
    bp.send_2byte_number(ammo);
    bp.send_4byte_float(angle);
    bp.send_1byte_number(power * 255);
    bp.send_4byte_float(countdown);
}
