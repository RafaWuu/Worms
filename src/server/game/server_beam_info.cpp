//
// Created by xguss on 03/11/23.
//

#include "server_beam_info.h"

BeamInfo::BeamInfo(const Beam& beam) {
    x = beam.body->GetPosition().x;
    y = beam.body->GetPosition().y;
    height = beam.height;
    width = beam.width;
    angle = beam.angle;
}
