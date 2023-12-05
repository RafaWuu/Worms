//
// Created by xguss on 02/12/23.
//

#ifndef WORMS_SERVER_PROVISION_INFO_H
#define WORMS_SERVER_PROVISION_INFO_H

#include "game/entities/server_gameobject_info.h"

#include "server_provision.h"

class ProvisionInfo: public GameObjectInfo {
private:
    float x;
    float y;
    ObjectType id;

public:
    explicit ProvisionInfo(const Provision& provision);
    void serialize_status(BaseProtocol& gp) override;

    void serialize_scenario(BaseProtocol& gp) override;
};
#endif  // WORMS_SERVER_PROVISION_INFO_H
