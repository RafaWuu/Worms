//
// Created by xguss on 03/11/23.
//

#include "server_beam_info.h"

BeamInfo::BeamInfo(const Beam& beam): beam(beam) {}

void BeamInfo::serialize_scenario(BaseProtocol& bp) {
    bp.send_1byte_number(beam.get_id());
    bp.send_4byte_float(beam.body->GetPosition().x);
    bp.send_4byte_float(beam.body->GetPosition().y);

    bp.send_4byte_float(beam.height);
    bp.send_4byte_float(beam.width);
    bp.send_4byte_float(beam.angle);
}
void BeamInfo::serialize_status(BaseProtocol& bp) { bp.send_1byte_number(beam.get_id()); }
