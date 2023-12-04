//
// Created by xguss on 03/11/23.
//

#include "server_beam_info.h"

BeamInfo::BeamInfo(const Beam& beam) {
    id = beam.get_id();
    x = beam.body->GetPosition().x;
    y = beam.body->GetPosition().y;

    height = beam.height;
    width = beam.width;
    angle = -beam.angle;
}

void BeamInfo::serialize_scenario(BaseProtocol& bp) {
    bp.send_1byte_number(id);
    bp.send_4byte_float(x);
    bp.send_4byte_float(y);

    bp.send_4byte_float(height);
    bp.send_4byte_float(width);
    bp.send_4byte_float(angle);
}
void BeamInfo::serialize_status(BaseProtocol& bp) { bp.send_1byte_number(id); }
