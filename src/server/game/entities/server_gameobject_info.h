//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_SERVER_GAMEOBJECT_INFO_H
#define WORMS_SERVER_GAMEOBJECT_INFO_H

#include "server_protocol.h"

class ServerProtocol;

class GameObjectInfo{

public:
    virtual void serialize_status(ServerProtocol& gp);

    virtual void serialize_scenario(ServerProtocol& gp);
};

#endif  // WORMS_SERVER_GAMEOBJECT_INFO_H
