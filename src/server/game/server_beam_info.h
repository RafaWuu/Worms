//
// Created by xguss on 03/11/23.
//

#ifndef WORMS_SERVER_BEAM_INFO_H
#define WORMS_SERVER_BEAM_INFO_H

#include "server_beam.h"

class BeamInfo {
public:
    explicit BeamInfo(const Beam& beam);
    float x;
    float y;
    float height;
    float width;
    float angle;
};
#endif  // WORMS_SERVER_BEAM_INFO_H
