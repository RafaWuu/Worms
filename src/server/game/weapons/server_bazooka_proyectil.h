//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_SERVER_BAZOOKA_PROYECTIL_H
#define WORMS_SERVER_BAZOOKA_PROYECTIL_H

#include <memory>

#include "game/entities/server_gameobject.h"
#include "game/entities/server_gameobject_info.h"

#include "b2_body.h"
#include "b2_world.h"

class GameWorld;

class BazookaProyectil: public GameObject {
private:
    b2Body* body;
    float dragConstant;

public:
    friend class BazookaProyectilInfo;

    explicit BazookaProyectil(b2World* world, b2Vec2& pos, float angle);
    ~BazookaProyectil();
    BazookaProyectil(const BazookaProyectil&) = delete;
    BazookaProyectil& operator=(const BazookaProyectil&) = delete;

    void update(b2World& world) override;
    std::unique_ptr<GameObjectInfo> get_status() const override;
    ObjectType get_id() const override;

    void on_proyectil_impact(GameWorld& world);
};
#endif  // WORMS_SERVER_BAZOOKA_PROYECTIL_H
