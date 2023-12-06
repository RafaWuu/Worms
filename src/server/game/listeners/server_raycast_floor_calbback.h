

#ifndef WORMS_SERVER_RAYCAST_FLOOR_CALBBACK_H
#define WORMS_SERVER_RAYCAST_FLOOR_CALBBACK_H

#include "game/entities/server_gameobject.h"
#include "game/entities/server_worm.h"

#include "box2d/b2_fixture.h"
#include "box2d/b2_math.h"
#include "box2d/b2_world_callbacks.h"

class RayCastFloorCallback: public b2RayCastCallback {
public:
    b2Body* m_body;
    b2Vec2 m_point;
    bool floor_was_hit;

    RayCastFloorCallback(): m_point(0, 0) {
        m_body = nullptr;
        floor_was_hit = false;
    }

    RayCastFloorCallback(const RayCastFloorCallback&) = delete;
    RayCastFloorCallback& operator=(const RayCastFloorCallback&) = delete;

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
                        float fraction) override {
        auto fixture_data = fixture->GetUserData().pointer;

        auto game_object = (GameObject*)fixture_data;

        if (game_object->get_id() == BEAM) {
            floor_was_hit = true;
        }

        m_body = fixture->GetBody();
        m_point = point;
        return fraction;
    }
};

#endif  // WORMS_SERVER_RAYCAST_FLOOR_CALBBACK_H
