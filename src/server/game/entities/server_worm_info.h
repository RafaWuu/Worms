//
// Created by xguss on 03/11/23.
//

#ifndef WORMS_SERVER_WORM_INFO_H
#define WORMS_SERVER_WORM_INFO_H

#include <cstdint>

#include "server_gameobject_info.h"

class Worm;

class WormInfo: public GameObjectInfo {

public:
    explicit WormInfo(const Worm& worm);

    const Worm& worm;

    void serialize_status(BaseProtocol& bp) override;
    void serialize_scenario(BaseProtocol& bp) override;
    void serialize_start(BaseProtocol& bp);
};
#endif  // WORMS_SERVER_WORM_INFO_H
