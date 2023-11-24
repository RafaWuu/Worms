//
// Created by xguss on 03/11/23.
//

#include "server_worm_info.h"

#include "server_worm.h"

#include "configuration/configuration.h"
#include "common_weapon_constants.h"

WormInfo::WormInfo(const Worm& worm) {
    object_id = worm.get_id();
    worm_id = worm.id;
    x = worm.body->GetPosition().x;
    y = worm.body->GetPosition().y;
    facing_right = worm.facing_right;
    state = worm.get_state();
    health = worm.health;
    weapon = BAZOOKA_ID;  // arma
    angle = worm.desiredAngle;
    power = worm.aim_power * 255;
    client_id = worm.client_id;
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
    bp.send_4byte_float(angle);
    bp.send_1byte_number(power * 255);
}
void WormInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(object_id);
    bp.send_2byte_number(worm_id);
    bp.send_4byte_float(x);
    bp.send_4byte_float(y);
    bp.send_1byte_number(facing_right);
    bp.send_2byte_number(state);
    bp.send_1byte_number(health);
    bp.send_1byte_number(weapon);  // arma
    bp.send_4byte_float(angle);
    bp.send_1byte_number(power * 255);
}

void WormInfo::serialize_start(BaseProtocol& bp) {
    bp.send_2byte_number(worm_id);
    bp.send_2byte_number(client_id);
}
