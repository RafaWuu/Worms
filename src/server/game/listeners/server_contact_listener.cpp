

#include "server_contact_listener.h"

#include "game/entities/server_gameobject.h"
#include "game/entities/server_worm_sensor.h"
#include "game/projectiles/server_melee_impact.h"
#include "game/provisions/server_provision.h"
#include "game/world/server_gameworld.h"

void ContactListener::BeginContact(b2Contact* contact) {

    auto fixtureUserDataA = contact->GetFixtureA()->GetUserData().pointer;
    auto fixtureUserDataB = contact->GetFixtureB()->GetUserData().pointer;

    auto game_objectA = (GameObject*)fixtureUserDataA;

    auto game_objectB = (GameObject*)fixtureUserDataB;


    // Worm toca el piso

    if (game_objectA->get_id() == WORM_SENSOR) {
        auto worm_sensor = dynamic_cast<WormSensor*>(game_objectA);
        worm_sensor->handle_begin_floor_contact(game_objectB);
    }

    if (game_objectB->get_id() == WORM_SENSOR) {
        auto* worm_sensor = dynamic_cast<WormSensor*>(game_objectB);
        worm_sensor->handle_begin_floor_contact(game_objectA);
    }

    // Proyectil impacta

    if (game_objectA->get_id() == projectile) {
        auto projectile = dynamic_cast<Projectile*>(game_objectA);
        projectile->on_projectile_impact(world);
    }

    if (game_objectB->get_id() == projectile) {
        auto* projectile = dynamic_cast<Projectile*>(game_objectB);
        projectile->on_projectile_impact(world);
    }

    // arma melee impacta

    if (game_objectA->get_id() == MELEE_SENSOR && game_objectB->get_id() == WORM) {
        auto* weapon = dynamic_cast<MeleeImpact*>(game_objectA);
        auto* worm = dynamic_cast<Worm*>(game_objectB);

        weapon->on_impact(world, *worm);
    }

    if (game_objectB->get_id() == MELEE_SENSOR && game_objectA->get_id() == WORM) {
        auto* weapon = dynamic_cast<MeleeImpact*>(game_objectB);
        auto* worm = dynamic_cast<Worm*>(game_objectA);

        weapon->on_impact(world, *worm);
    }

    // provision tomada

    if (game_objectA->get_id() == PROVISION && game_objectB->get_id() == WORM) {
        auto* provision = dynamic_cast<Provision*>(game_objectA);
        auto* worm = dynamic_cast<Worm*>(game_objectB);

        provision->take(world, *worm);
    }

    if (game_objectB->get_id() == PROVISION && game_objectA->get_id() == WORM) {
        auto* provision = dynamic_cast<Provision*>(game_objectB);
        auto* worm = dynamic_cast<Worm*>(game_objectA);

        provision->take(world, *worm);
    }
}


void ContactListener::EndContact(b2Contact* contact) {

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

ContactListener::ContactListener(GameWorld& world): world(world) {}
