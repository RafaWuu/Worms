//
// Created by xguss on 29/11/23.
//

#ifndef WORMS_SERVER_EXPLOSION_H
#define WORMS_SERVER_EXPLOSION_H

#include "server_gameobject.h"

class Explosion: public GameObject {
private:
    int frames;
    uint16_t type;
    float radius;
    float pos_y;
    float pos_x;

public:
    friend class ExplosionInfo;

    Explosion(uint16_t projectile_type, float radius, b2Vec2 center);
    ObjectType get_id() const override;
    std::unique_ptr<GameObjectInfo> get_status() const override;
    void update(GameWorld& world) override;
};

#endif  // WORMS_SERVER_EXPLOSION_H
