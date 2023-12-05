

#ifndef WORMS_SERVER_MELEE_IMPACT_INFO_H
#define WORMS_SERVER_MELEE_IMPACT_INFO_H

#include "game/entities/server_gameobject.h"
#include "game/entities/server_gameobject_info.h"

#include "server_melee_impact.h"

class MeleeSensorInfo: public GameObjectInfo {
private:
    ObjectType id;

public:
    explicit MeleeSensorInfo(const MeleeImpact& object);
    void serialize_status(BaseProtocol& gp) override;

    void serialize_scenario(BaseProtocol& gp) override;
};
#endif  // WORMS_SERVER_MELEE_IMPACT_INFO_H
