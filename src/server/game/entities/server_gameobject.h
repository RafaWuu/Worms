//
// Created by xguss on 04/11/23.
//

#ifndef WORMS_SERVER_GAMEOBJECT_H
#define WORMS_SERVER_GAMEOBJECT_H

#include <memory>

#include "b2_world.h"
#include "common_log.h"
#include "server_gameobject_info.h"

class GameWorld;

enum ObjectType {
    GROUND = 0x001,
    BEAM = 0x002,
    WORM = 0x004,
    BOUNDARY = 0x006,
    WORM_SENSOR = 0x008,
    projectile = 0x0010,
    BOX = 0x0020,
    EXPLOSION = 0x0040,
};

class GameObject {
public:
    static Log& getLog();
    bool is_dead = false;

public:
    virtual ObjectType get_id() const = 0;
    virtual ~GameObject() = default;
    virtual std::unique_ptr<GameObjectInfo> get_status() const = 0;
    virtual void update(GameWorld& world);
    virtual void delete_body();
};
#endif  // WORMS_SERVER_GAMEOBJECT_H
