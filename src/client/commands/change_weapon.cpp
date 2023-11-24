#include "change_weapon.h"

ChangeWeapon::ChangeWeapon(int weapon_id) : weapon_id(weapon_id) {}

void ChangeWeapon::serialize(ClientProtocol& protocol) { return protocol.serialize_change_weapon(weapon_id); }
