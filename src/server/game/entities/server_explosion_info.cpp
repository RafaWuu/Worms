//
// Created by xguss on 29/11/23.
//

#include "server_explosion_info.h"

ExplosionInfo::ExplosionInfo(const Explosion& explosion) {
    id = explosion.get_id();
    type = explosion.type;
    radius = explosion.radius;
    x = explosion.pos_x;
    y = explosion.pos_y;
}

void ExplosionInfo::serialize_scenario(BaseProtocol& bp) { bp.send_1byte_number(id); }
void ExplosionInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(id);
    bp.send_2byte_number(type);
    bp.send_4byte_float(radius);
    bp.send_4byte_float(x);
    bp.send_4byte_float(y);
}
