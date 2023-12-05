

#ifndef WORMS_BAZOOKA_projectile_INFO_H
#define WORMS_BAZOOKA_projectile_INFO_H

#include "game/entities/server_gameobject_info.h"

#include "server_projectile.h"
class ProjectileInfo: public GameObjectInfo {
private:
    ObjectType id;
    int type;
    float x;
    float y;
    float angle;

public:
    explicit ProjectileInfo(const Projectile& projectile);
    void serialize_status(BaseProtocol& gp) override;

    void serialize_scenario(BaseProtocol& gp) override;
};
#endif  // WORMS_BAZOOKA_projectile_INFO_H
