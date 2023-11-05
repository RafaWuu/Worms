//
// Created by xguss on 05/11/23.
//

#include "server_onfloor_contactlistener.h"

#include "server_gameobject.h"
#include "server_worm_sensor.h"

void OnFloorContactListener::BeginContact(b2Contact* contact) {

    auto fixtureUserDataA = contact->GetFixtureA()->GetUserData().pointer;
    auto fixtureUserDataB = contact->GetFixtureB()->GetUserData().pointer;

    // cppcheck-suppress cstyleCast
    auto game_objectA = (GameObject*)fixtureUserDataA;

    // cppcheck-suppress cstyleCast
    auto game_objectB = (GameObject*)fixtureUserDataB;

    if (game_objectA->get_id() == WORM_SENSOR) {
        auto worm_sensor = dynamic_cast<WormSensor*>(game_objectA);
        worm_sensor->handle_begin_floor_contact(game_objectB);
    }

    if (game_objectB->get_id() == WORM_SENSOR) {
        auto worm_sensor = dynamic_cast<WormSensor*>(game_objectA);
        worm_sensor->handle_begin_floor_contact(game_objectA);
    }
}


void OnFloorContactListener::EndContact(b2Contact* contact) {

    auto fixtureUserDataA = contact->GetFixtureA()->GetUserData().pointer;
    auto fixtureUserDataB = contact->GetFixtureB()->GetUserData().pointer;

    // cppcheck-suppress cstyleCast
    auto game_objectA = (GameObject*)fixtureUserDataA;

    // cppcheck-suppress cstyleCast
    auto game_objectB = (GameObject*)fixtureUserDataB;

    if (game_objectA->get_id() == WORM_SENSOR) {
        auto worm_sensor = dynamic_cast<WormSensor*>(game_objectA);
        worm_sensor->handle_end_floor_contact(game_objectB);
    }

    if (game_objectB->get_id() == WORM_SENSOR) {
        auto worm_sensor = dynamic_cast<WormSensor*>(game_objectA);
        worm_sensor->handle_end_floor_contact(game_objectA);
    }
}
