//
// Created by xguss on 05/11/23.
//

#include "server_onfloor_contactlistener.h"

#include "game/entities/server_gameobject.h"
#include "game/entities/server_worm_sensor.h"
#include "game/world/server_gameworld.h"

void OnFloorContactListener::BeginContact(b2Contact* contact) {

    auto fixtureUserDataA = contact->GetFixtureA()->GetUserData().pointer;
    auto fixtureUserDataB = contact->GetFixtureB()->GetUserData().pointer;

    auto game_objectA = (GameObject*)fixtureUserDataA;

    auto game_objectB = (GameObject*)fixtureUserDataB;

    if (game_objectA->get_id() == WORM_SENSOR) {
        auto worm_sensor = dynamic_cast<WormSensor*>(game_objectA);
        worm_sensor->handle_begin_floor_contact(game_objectB);
    }

    if (game_objectB->get_id() == WORM_SENSOR) {
        auto* worm_sensor = dynamic_cast<WormSensor*>(game_objectB);
        worm_sensor->handle_begin_floor_contact(game_objectA);
    }

    if (game_objectA->get_id() == projectile) {
        auto projectile = dynamic_cast<Projectile*>(game_objectA);
        projectile->on_projectile_impact(world);
    }

    if (game_objectB->get_id() == projectile) {
        auto* projectile = dynamic_cast<Projectile*>(game_objectB);
        projectile->on_projectile_impact(world);
    }
}


void OnFloorContactListener::EndContact(b2Contact* contact) {

    auto fixtureUserDataA = contact->GetFixtureA()->GetUserData().pointer;
    auto fixtureUserDataB = contact->GetFixtureB()->GetUserData().pointer;

    auto game_objectA = (GameObject*)fixtureUserDataA;

    auto game_objectB = (GameObject*)fixtureUserDataB;

    if (game_objectA->get_id() == WORM_SENSOR) {
        auto worm_sensor = dynamic_cast<WormSensor*>(game_objectA);
        worm_sensor->handle_end_floor_contact(game_objectB);
    }

    if (game_objectB->get_id() == WORM_SENSOR) {
        auto worm_sensor = dynamic_cast<WormSensor*>(game_objectB);
        worm_sensor->handle_end_floor_contact(game_objectA);
    }
}

OnFloorContactListener::OnFloorContactListener(GameWorld& world): world(world) {}
