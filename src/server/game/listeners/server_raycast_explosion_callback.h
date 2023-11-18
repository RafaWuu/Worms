//
// Created by xguss on 18/11/23.
//

#ifndef WORMS_SERVER_RAYCAST_EXPLOSION_CALLBACK_H
#define WORMS_SERVER_RAYCAST_EXPLOSION_CALLBACK_H


#include "game/entities/server_gameobject.h"
#include "game/entities/server_worm.h"

#include "b2_fixture.h"
#include "b2_math.h"
#include "b2_world_callbacks.h"

class RayCastExplosionCallback: public b2RayCastCallback {
public:
    b2Body* m_body;
    b2Vec2 m_point;
    Worm* p_worm;
    RayCastExplosionCallback(): m_point(0, 0) {
        m_body = nullptr;
        p_worm = nullptr;
    }

    RayCastExplosionCallback(const RayCastExplosionCallback&) = delete;
    RayCastExplosionCallback& operator=(const RayCastExplosionCallback&) = delete;

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal,
                        float fraction) override {
        auto fixture_data = fixture->GetUserData().pointer;

        auto game_object = (GameObject*)fixture_data;

        if (game_object->get_id() == WORM) {
            p_worm = dynamic_cast<Worm*>(game_object);
        }

        m_body = fixture->GetBody();
        m_point = point;
        return fraction;
    }
};
#endif  // WORMS_SERVER_RAYCAST_EXPLOSION_CALLBACK_H
