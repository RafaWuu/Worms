//
// Created by xguss on 03/11/23.
//

#ifndef WORMS_SERVER_BEAM_H
#define WORMS_SERVER_BEAM_H

#include "b2_body.h"

class Beam {
private:
    b2Body* body;
    float height;
    float width;
    float angle;

public:
    friend class BeamInfo;
    Beam(b2Body* body, float width, float height, float angle);
};

#endif  // WORMS_SERVER_BEAM_H
