

#include "server_weapon_info_grenade.h"

#include "common_weapon_constants.h"

GrenadeWeaponInfo::GrenadeWeaponInfo(const GrenadeWeapon& grenade) {
    power = grenade.aim_power;
    angle = grenade.aim_angle;
    countdown = grenade.countdown;
}

void GrenadeWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(GREEN_GRENADE_ID);
    bp.send_4byte_float(angle);
    bp.send_1byte_number(power * 255);
    bp.send_4byte_float(countdown);
}
