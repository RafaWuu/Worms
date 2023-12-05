

#include "server_weapon_info_teleportation.h"

#include "common_weapon_constants.h"


TeleportationWeaponInfo::TeleportationWeaponInfo(const TeleportationWeapon& object) {
    aim_x = object.aim_x;
    aim_y = object.aim_y;
}

void TeleportationWeaponInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(TELEPORTATION_ID);
    bp.send_4byte_float(aim_x);
    bp.send_4byte_float(aim_y);
}
