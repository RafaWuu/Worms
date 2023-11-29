#include "change_weapon.h"

ChangeWeapon::ChangeWeapon(int weapon_id): weapon_id(weapon_id) {}

void ChangeWeapon::serialize(uint16_t worm, ClientProtocol& protocol) {
    return protocol.serialize_change_weapon(worm, weapon_id);
}
