//
// Created by xguss on 03/11/23.
//

#ifndef WORMS_SERVER_WORM_INFO_H
#define WORMS_SERVER_WORM_INFO_H

#include <cstdint>

#include "server_gameobject.h"
#include "server_gameobject_info.h"

class Worm;

class WormInfo: public GameObjectInfo {
private:
    ObjectType object_id;
    float x;
    float y;
    float angle;
    uint16_t worm_id;
    bool facing_right;
    uint16_t state;
    uint8_t health;
    int weapon;
    float power;
    uint16_t client_id;

public:
    explicit WormInfo(const Worm& worm);

    void serialize_status(BaseProtocol& bp) override;
    void serialize_scenario(BaseProtocol& bp) override;


    void serialize_start(BaseProtocol& bp);
};
#endif  // WORMS_SERVER_WORM_INFO_H
