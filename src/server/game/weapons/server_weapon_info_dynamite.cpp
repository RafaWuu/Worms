

#include "server_weapon_info_dynamite.h"

#include "common_weapon_constants.h"

DynamiteWeaponInfo::DynamiteWeaponInfo(const DynamiteWeapon& dynamite) {
    ammo = dynamite.ammo;
    countdown = dynamite.countdown;
}

void DynamiteWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(DYNAMITE_ID);
    bp.send_2byte_number(ammo);
    bp.send_4byte_float(countdown);
}
