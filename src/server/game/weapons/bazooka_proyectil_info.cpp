//
// Created by xguss on 14/11/23.
//

#include "bazooka_proyectil_info.h"
BazookaProyectilInfo::BazookaProyectilInfo(const BazookaProyectil& proyectil):
        proyectil(proyectil) {

}
void BazookaProyectilInfo::serialize_status(ServerProtocol& gp) {
    gp.send_1byte_number(proyectil.get_id());
    gp.send_1byte_number(1);
    gp.send_4byte_float(proyectil.body->GetPosition().x);
    gp.send_4byte_float(proyectil.body->GetPosition().y);
}
void BazookaProyectilInfo::serialize_scenario(ServerProtocol& gp) {
    gp.send_1byte_number(proyectil.get_id());

}
