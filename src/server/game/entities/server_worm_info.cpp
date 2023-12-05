

#include "server_worm_info.h"

#include <utility>

#include "../../configuration/configuration.h"

#include "common_weapon_constants.h"
#include "server_worm.h"

WormInfo::WormInfo(const Worm& worm) {
    object_id = worm.get_id();
    worm_id = worm.id;
    x = worm.body->GetPosition().x;
    y = worm.body->GetPosition().y;
    facing_right = worm.facing_right;
    state = worm.get_state();
    health = worm.health;
    weapon = worm.current_weapon;  // arma
    client_id = worm.client_id;
    weapon_info = worm.get_current_weapon_info();
}

WormInfo::WormInfo(ObjectType object_id, float x, float y, uint16_t worm_id, bool facing_right,
                   uint16_t state, uint8_t health, int current_weapon, uint16_t client_id,
                   std::unique_ptr<WeaponInfo> weapon_info):
        weapon_info(std::move(weapon_info)) {
    this->object_id = object_id;
    this->worm_id = worm_id;
    this->x = x;
    this->y = y;
    this->facing_right = facing_right;
    this->state = state;
    this->health = health;
    this->weapon = current_weapon;  // arma
    this->client_id = client_id;
}

void WormInfo::serialize_scenario(BaseProtocol& bp) {
    bp.send_1byte_number(object_id);
    bp.send_2byte_number(worm_id);
    bp.send_4byte_float(x);
    bp.send_4byte_float(y);
    bp.send_1byte_number(facing_right);
    bp.send_2byte_number(state);
    bp.send_1byte_number(health);
    bp.send_1byte_number(weapon);  // arma
}
void WormInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(object_id);
    bp.send_2byte_number(worm_id);
    bp.send_4byte_float(x);
    bp.send_4byte_float(y);
    bp.send_1byte_number(facing_right);
    bp.send_2byte_number(state);
    bp.send_1byte_number(health);
    weapon_info->serialize_status(bp);
}

void WormInfo::serialize_start(BaseProtocol& bp) {
    bp.send_2byte_number(worm_id);
    bp.send_2byte_number(client_id);
}
