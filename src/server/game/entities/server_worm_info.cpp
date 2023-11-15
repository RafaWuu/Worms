//
// Created by xguss on 03/11/23.
//

#include "server_worm_info.h"

#include "server_worm.h"

WormInfo::WormInfo(const Worm& worm) : worm(worm){
}

void WormInfo::serialize_scenario(ServerProtocol& gp) {
    gp.send_1byte_number(worm.get_id());
    gp.send_2byte_number(worm.id);
    gp.send_4byte_float(worm.body->GetPosition().x);
    gp.send_4byte_float(worm.body->GetPosition().y);
    gp.send_1byte_number(worm.facing_right);
    gp.send_2byte_number(worm.get_state());
    gp.send_1byte_number(worm.health);
}
void WormInfo::serialize_status(ServerProtocol& gp) {
    gp.send_1byte_number(worm.get_id());
    gp.send_2byte_number(worm.id);
    gp.send_4byte_float(worm.body->GetPosition().x);
    gp.send_4byte_float(worm.body->GetPosition().y);
    gp.send_1byte_number(worm.facing_right);
    gp.send_2byte_number(worm.get_state());
    gp.send_1byte_number(worm.health);
}

void WormInfo::serialize_start(ServerProtocol& gp) {
    gp.send_2byte_number(worm.id);
    gp.send_2byte_number(worm.client_id);
}