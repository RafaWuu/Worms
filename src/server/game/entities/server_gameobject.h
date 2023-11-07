//
// Created by xguss on 04/11/23.
//

#ifndef WORMS_SERVER_GAMEOBJECT_H
#define WORMS_SERVER_GAMEOBJECT_H

#include "common_log.h"

enum ObjectType { BOUNDARIE = 1, BEAM = 2, WORM = 3, WORM_SENSOR = 4, PROJECTIL = 5, BOX = 6 };

class GameObject {
public:
    static Log& getLog();

public:
    virtual ObjectType get_id() = 0;
};
#endif  // WORMS_SERVER_GAMEOBJECT_H
