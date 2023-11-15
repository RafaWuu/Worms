//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_BAZOOKA_PROYECTIL_INFO_H
#define WORMS_BAZOOKA_PROYECTIL_INFO_H

#include "game/entities/server_gameobject_info.h"

#include "server_bazooka_proyectil.h"
class BazookaProyectilInfo : public GameObjectInfo {
private:
    const BazookaProyectil& proyectil;
public:
    BazookaProyectilInfo(const BazookaProyectil& proyectil);
    void serialize_status(ServerProtocol &gp) override;
    void serialize_scenario(ServerProtocol &gp) override;
};
#endif  // WORMS_BAZOOKA_PROYECTIL_INFO_H
