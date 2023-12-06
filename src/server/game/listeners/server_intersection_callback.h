//
// Created by xguss on 06/12/23.
//

#ifndef WORMS_SERVER_INTERSECTION_CALLBACK_H
#define WORMS_SERVER_INTERSECTION_CALLBACK_H

#include "box2d/b2_world_callbacks.h"
#include "game/entities/server_gameobject.h"
#include "box2d/b2_fixture.h"

class IntersectionCallback: public b2QueryCallback {
public:
    bool intersecting = false;
    bool ReportFixture(b2Fixture* fixture) override {
        auto fixture_data = fixture->GetUserData().pointer;

        auto game_object = reinterpret_cast<GameObject*>(fixture_data);

        auto id = game_object->get_id();
        if (id == BEAM || id == BOUNDARY) {
            intersecting = true;
            return false;
        }
        return true;
    }
};

#endif //WORMS_SERVER_INTERSECTION_CALLBACK_H
