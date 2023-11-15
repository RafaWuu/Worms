//
// Created by xguss on 05/11/23.
//

#ifndef WORMS_SERVER_GROUND_H
#define WORMS_SERVER_GROUND_H

#include "b2_body.h"
#include "b2_world.h"
#include "server_gameobject.h"

class Ground: public GameObject {
private:
    b2Body* body;
public:
    friend class GroundInfo;

    explicit Ground(b2World* world);
    ObjectType get_id() const override;
    std::unique_ptr<GameObjectInfo> get_status() const override;
    float width;
    float height;
};
#endif  // WORMS_SERVER_GROUND_H
