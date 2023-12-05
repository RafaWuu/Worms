#ifndef __DESKTOP_OG_MAIN_BRANCH_WORMS_SRC_SERVER_GAME_ENTITIES_SERVER_BOUNDARY_H_
#define __DESKTOP_OG_MAIN_BRANCH_WORMS_SRC_SERVER_GAME_ENTITIES_SERVER_BOUNDARY_H_

#include <memory>

#include "b2_body.h"
#include "b2_world.h"
#include "server_gameobject.h"

class Boundary: public GameObject {
private:
    float height;
    float width;

    b2Body* body;

public:
    Boundary(b2World* b2_world, float width, float height, float frontier);
    ObjectType get_id() const override;

    std::unique_ptr<GameObjectInfo> get_status() const override;
};

#endif  // __DESKTOP_OG_MAIN_BRANCH_WORMS_SRC_SERVER_GAME_ENTITIES_SERVER_BOUNDARY_H_
