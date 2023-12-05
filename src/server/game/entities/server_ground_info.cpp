//
// Created by xguss on 14/11/23.
//

#include "server_ground_info.h"

GroundInfo::GroundInfo(const Ground& ground) {
    id = ground.get_id();
    x = ground.body->GetPosition().x;
    y = ground.body->GetPosition().y;
    height = ground.height;
    width = ground.width;
}

void GroundInfo::serialize_scenario(BaseProtocol& bp) {
    bp.send_1byte_number(id);
    bp.send_4byte_float(x);
    bp.send_4byte_float(y);

    bp.send_4byte_float(width);
    bp.send_4byte_float(height);
}
void GroundInfo::serialize_status(BaseProtocol& bp) { bp.send_1byte_number(id); }
