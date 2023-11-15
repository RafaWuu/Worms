//
// Created by xguss on 11/11/23.
//

#include "server_weapon.h"
#include "server_bazooka_proyectil.h"
#include "game/world/server_gameworld.h"


void Weapon::fire_proyectil(b2Vec2 pos, float angle) {
    world.add_proyectil(std::make_shared<BazookaProyectil>(&world.b2_world, pos, angle));
}
Weapon::Weapon(GameWorld& world): world(world) {
}
