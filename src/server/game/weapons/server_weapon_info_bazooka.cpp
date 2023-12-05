

#include "server_weapon_info_bazooka.h"

#include "common_weapon_constants.h"

BazookaWeaponInfo::BazookaWeaponInfo(const BazookaWeapon& bazooka) {

    angle = bazooka.aim_angle;
    power = bazooka.aim_power;
    ammo = bazooka.ammo;
}

void BazookaWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(BAZOOKA_ID);
    bp.send_4byte_float(angle);
    bp.send_1byte_number(power * 255);
}

BazookaWeaponInfo::BazookaWeaponInfo(float angle, float power, float ammo) {
    this->angle = angle;
    this->power = power;
    this->ammo = ammo;
}
