//
// Created by xguss on 03/11/23.
//

#include "server_beam_info.h"

BeamInfo::BeamInfo(const Beam& beam) : beam(beam) {
}

void BeamInfo::serialize_scenario(ServerProtocol& gp) {
    gp.send_1byte_number(beam.get_id());
    gp.send_4byte_float(beam.body->GetPosition().x);
    gp.send_4byte_float(beam.body->GetPosition().y);

    gp.send_4byte_float(beam.height);
    gp.send_4byte_float(beam.width);
    gp.send_4byte_float(beam.angle);

}
void BeamInfo::serialize_status(ServerProtocol& gp) {
    gp.send_1byte_number(beam.get_id());
}
