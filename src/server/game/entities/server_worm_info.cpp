//
// Created by xguss on 03/11/23.
//

#include "server_worm_info.h"

#include "server_worm.h"

WormInfo::WormInfo(const Worm& worm): worm(worm) {}

void WormInfo::serialize_scenario(BaseProtocol& bp) {
    bp.send_1byte_number(worm.get_id());
    bp.send_2byte_number(worm.id);
    bp.send_4byte_float(worm.body->GetPosition().x);
    bp.send_4byte_float(worm.body->GetPosition().y);
    bp.send_1byte_number(worm.facing_right);
    bp.send_2byte_number(worm.get_state());
    bp.send_1byte_number(worm.health);
}
void WormInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(worm.get_id());
    bp.send_2byte_number(worm.id);
    bp.send_4byte_float(worm.body->GetPosition().x);
    bp.send_4byte_float(worm.body->GetPosition().y);
    bp.send_1byte_number(worm.facing_right);
    bp.send_2byte_number(worm.get_state());
    bp.send_1byte_number(worm.health);
}

void WormInfo::serialize_start(BaseProtocol& bp) {
    bp.send_2byte_number(worm.id);
    bp.send_2byte_number(worm.client_id);
}
