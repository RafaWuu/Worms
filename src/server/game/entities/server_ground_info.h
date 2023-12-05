

#ifndef WORMS_SERVER_GROUND_INFO_H
#define WORMS_SERVER_GROUND_INFO_H

#include "server_gameobject_info.h"
#include "server_ground.h"
class GroundInfo: public GameObjectInfo {
private:
    ObjectType id;
    float x;
    float y;
    float height;
    float width;

public:
    explicit GroundInfo(const Ground& ground);

    void serialize_scenario(BaseProtocol& bp) override;
    void serialize_status(BaseProtocol& bp) override;
};

#endif  // WORMS_SERVER_GROUND_INFO_H
