

#ifndef WORMS_SERVER_EXPLOSION_CALLBACK_H
#define WORMS_SERVER_EXPLOSION_CALLBACK_H


#include <vector>

#include "game/entities/server_gameobject.h"
#include "game/entities/server_worm.h"

#include "b2_fixture.h"
#include "b2_math.h"
#include "b2_world_callbacks.h"

class ExplosionCallback: public b2QueryCallback {
public:
    std::vector<b2Body*> found_bodies;
    std::vector<Worm*> found_worms;

    bool ReportFixture(b2Fixture* fixture) override {
        auto fixture_data = fixture->GetUserData().pointer;

        auto game_object = (GameObject*)fixture_data;

        if (game_object->get_id() == WORM) {
            found_bodies.push_back(fixture->GetBody());
            found_worms.push_back(dynamic_cast<Worm*>(game_object));
        }

        return true;  // keep going to find all fixtures in the query area
    }
};
#endif  // WORMS_SERVER_EXPLOSION_CALLBACK_H
