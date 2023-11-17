//
// Created by xguss on 14/11/23.
//

#include "server_ground_info.h"

GroundInfo::GroundInfo(const Ground& ground): ground(ground) {}

void GroundInfo::serialize_scenario(BaseProtocol& bp) {
    bp.send_1byte_number(ground.get_id());
    bp.send_4byte_float(ground.body->GetPosition().x);
    bp.send_4byte_float(ground.body->GetPosition().y);
    bp.send_4byte_float(ground.height);
    bp.send_4byte_float(ground.width);
}
void GroundInfo::serialize_status(BaseProtocol& bp) { bp.send_1byte_number(ground.get_id()); }
