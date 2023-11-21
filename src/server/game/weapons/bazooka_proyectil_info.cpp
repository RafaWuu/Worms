//
// Created by xguss on 14/11/23.
//

#include "bazooka_proyectil_info.h"

BazookaProyectilInfo::BazookaProyectilInfo(const BazookaProyectil& proyectil):
        id(proyectil.get_id()) {
    type = 1;
    x = proyectil.body->GetPosition().x;
    y = proyectil.body->GetPosition().y;
}
void BazookaProyectilInfo::serialize_status(BaseProtocol& gp) {
    gp.send_1byte_number(id);
    gp.send_1byte_number(type);
    gp.send_4byte_float(x);
    gp.send_4byte_float(y);
}
void BazookaProyectilInfo::serialize_scenario(BaseProtocol& gp) { gp.send_1byte_number(id); }
