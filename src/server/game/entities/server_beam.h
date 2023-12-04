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
    Beam(b2World* b2_world, float center_x, float center_y, float width, float height, bool flip,
         float angle);
    ObjectType get_id() const override;
    std::unique_ptr<GameObjectInfo> get_status() const override;

    bool is_walkable();
};

#endif  // WORMS_SERVER_BEAM_H
