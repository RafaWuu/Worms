//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_SERVER_GAMEOBJECT_INFO_H
#define WORMS_SERVER_GAMEOBJECT_INFO_H

#include "../src/server/server_protocol.h"

class ServerProtocol;

class GameObjectInfo {

public:
    virtual ~GameObjectInfo() = default;
    virtual void serialize_status(BaseProtocol& gp);

    virtual void serialize_scenario(BaseProtocol& gp);
};

#endif  // WORMS_SERVER_GAMEOBJECT_INFO_H
