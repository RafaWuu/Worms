

#include "server_weapon_info_holygrenade.h"

#include "common_weapon_constants.h"

HolyGrenadeWeaponInfo::HolyGrenadeWeaponInfo(const HolyGrenadeWeapon& grenade) {
    ammo = grenade.ammo;
    angle = grenade.aim_angle;
    power = grenade.aim_power;
    countdown = grenade.countdown;
}

void HolyGrenadeWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(HOLY_GRENADE_ID);
    bp.send_2byte_number(ammo);
    bp.send_4byte_float(angle);
    bp.send_1byte_number(power * UINT8_MAX);
    bp.send_4byte_float(countdown);
}
