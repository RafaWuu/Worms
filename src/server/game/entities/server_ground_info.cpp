//
// Created by xguss on 14/11/23.
//

#include "server_ground_info.h"

GroundInfo::GroundInfo(const Ground& ground) : ground(ground) {
}

void GroundInfo::serialize_scenario(ServerProtocol& gp) {
    gp.send_1byte_number(ground.get_id());
    gp.send_4byte_float(ground.body->GetPosition().x);
    gp.send_4byte_float(ground.body->GetPosition().y);
    gp.send_4byte_float(ground.height);
    gp.send_4byte_float(ground.width);

}
void GroundInfo::serialize_status(ServerProtocol& gp) {
    gp.send_1byte_number(ground.get_id());

}