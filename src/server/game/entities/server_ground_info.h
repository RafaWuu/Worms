//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_SERVER_GROUND_INFO_H
#define WORMS_SERVER_GROUND_INFO_H

#include "server_gameobject_info.h"
#include "server_ground.h"
class GroundInfo : public GameObjectInfo {
public:
    explicit GroundInfo(const Ground& ground);
    const Ground& ground;

    void serialize_scenario(ServerProtocol &gp) override;
    void serialize_status(ServerProtocol &gp) override;
};

#endif  // WORMS_SERVER_GROUND_INFO_H
