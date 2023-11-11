//
// Created by xguss on 04/11/23.
//

#ifndef WORMS_SERVER_GAMEOBJECT_H
#define WORMS_SERVER_GAMEOBJECT_H

#include "common_log.h"

enum ObjectType { BOUNDARIE = 0x001,
        BEAM = 0x002,
        WORM = 0x004,
        WORM_SENSOR = 0x008,
        PROJECTIL = 0x0010,
        BOX = 0x0020 };

class GameObject {
public:
    static Log& getLog();

public:
    virtual ObjectType get_id() = 0;
};
#endif  // WORMS_SERVER_GAMEOBJECT_H
