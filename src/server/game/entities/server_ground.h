//
// Created by xguss on 05/11/23.
//

#ifndef WORMS_SERVER_GROUND_H
#define WORMS_SERVER_GROUND_H

#include "b2_world.h"
#include "server_gameobject.h"

class Ground: public GameObject {
public:
    explicit Ground(b2World* world);
    ObjectType get_id() override;
};
#endif  // WORMS_SERVER_GROUND_H
