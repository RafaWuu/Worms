#ifndef __DESKTOP_OG_MAIN_BRANCH_WORMS_SRC_SERVER_GAME_ENTITIES_SERVER_BOUNDARY_H_
#define __DESKTOP_OG_MAIN_BRANCH_WORMS_SRC_SERVER_GAME_ENTITIES_SERVER_BOUNDARY_H_

#include "b2_body.h"
#include "b2_world.h"
#include "server_gameobject.h"

class Boundary: public GameObject {
private:
    b2Body* edge_1;
    b2Body* edge_2;
    b2Body* edge_3;
    float height;
    float width;

    float pos_x;
    float pos_y;

public:

    Boundary(b2World* b2_world, float width, float height);
    ObjectType get_id() const override;
    std::unique_ptr<GameObjectInfo> get_status() const override;
};

#endif // __DESKTOP_OG_MAIN_BRANCH_WORMS_SRC_SERVER_GAME_ENTITIES_SERVER_BOUNDARY_H_