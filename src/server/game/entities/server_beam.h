//
// Created by xguss on 03/11/23.
//

#ifndef WORMS_SERVER_BEAM_H
#define WORMS_SERVER_BEAM_H

#include "b2_body.h"
#include "b2_world.h"
#include "server_gameobject.h"

class Beam: public GameObject {
private:
    b2Body* body;
    float height;
    float width;
    float angle;

    float pos_x;
    float pos_y;

public:
    friend class BeamInfo;
    Beam(b2World* b2_world, float center_x, float center_y, float width, float height, float angle);
    ObjectType get_id() override;
};

#endif  // WORMS_SERVER_BEAM_H
