

#ifndef WORMS_SERVER_GAMEOBJECT_INFO_H
#define WORMS_SERVER_GAMEOBJECT_INFO_H

#include "server_protocol.h"

class ServerProtocol;

class GameObjectInfo {

public:
    virtual ~GameObjectInfo() = default;
    virtual void serialize_status(BaseProtocol& gp);

    virtual void serialize_scenario(BaseProtocol& gp);
};

#endif  // WORMS_SERVER_GAMEOBJECT_INFO_H
