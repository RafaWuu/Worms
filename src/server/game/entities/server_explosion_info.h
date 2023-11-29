//
// Created by xguss on 29/11/23.
//

#ifndef WORMS_SERVER_EXPLOSION_INFO_H
#define WORMS_SERVER_EXPLOSION_INFO_H

#include "server_explosion.h"
#include "server_gameobject_info.h"

class ExplosionInfo: public GameObjectInfo {
private:
    ObjectType id;
    uint16_t type;
    float x;
    float y;
    float radius;

public:
    explicit ExplosionInfo(const Explosion& explosion);

    void serialize_scenario(BaseProtocol& bp) override;

    void serialize_status(BaseProtocol& gp) override;
};

#endif  // WORMS_SERVER_EXPLOSION_INFO_H
