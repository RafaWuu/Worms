//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_BAZOOKA_PROYECTIL_INFO_H
#define WORMS_BAZOOKA_PROYECTIL_INFO_H

#include "game/entities/server_gameobject_info.h"

#include "server_bazooka_proyectil.h"
class BazookaProyectilInfo: public GameObjectInfo {
private:
    const BazookaProyectil& proyectil;

public:
    explicit BazookaProyectilInfo(const BazookaProyectil& proyectil);
    void serialize_status(BaseProtocol& gp) override;
    void serialize_scenario(BaseProtocol& gp) override;
};
#endif  // WORMS_BAZOOKA_PROYECTIL_INFO_H
