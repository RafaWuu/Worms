//
// Created by xguss on 04/11/23.
//

#ifndef WORMS_SERVER_GAMEOBJECT_H
#define WORMS_SERVER_GAMEOBJECT_H

#include <memory>

#include "b2_world.h"
#include "common_log.h"
#include "server_gameobject_info.h"

enum ObjectType {
    GROUND = 0x001,
    BEAM = 0x002,
    WORM = 0x004,
    WORM_SENSOR = 0x008,
    PROYECTIL = 0x0010,
    BOX = 0x0020
};

class GameObject {
public:
    static Log& getLog();
    bool is_dead = false;

public:
    virtual ObjectType get_id() const = 0;
    virtual std::unique_ptr<GameObjectInfo> get_status() const = 0;
    virtual void update(b2World& world);
    // recuerden tener destructores virtuales cuando usen herencia!
    virtual ~GameObject() = default;
};
#endif  // WORMS_SERVER_GAMEOBJECT_H
