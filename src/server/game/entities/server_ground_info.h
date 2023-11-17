//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_SERVER_GROUND_INFO_H
#define WORMS_SERVER_GROUND_INFO_H

#include "server_gameobject_info.h"
#include "server_ground.h"
class GroundInfo: public GameObjectInfo {
public:
    explicit GroundInfo(const Ground& ground);
    const Ground& ground;

    void serialize_scenario(BaseProtocol& bp) override;
    void serialize_status(BaseProtocol& bp) override;
};

#endif  // WORMS_SERVER_GROUND_INFO_H
