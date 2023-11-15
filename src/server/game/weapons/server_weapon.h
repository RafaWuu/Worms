//
// Created by xguss on 11/11/23.
//

#ifndef WORMS_SERVER_WEAPON_H
#define WORMS_SERVER_WEAPON_H


#include <memory>

#include "b2_math.h"
class GameWorld;
class BazookaProyectil;

class Weapon{
private:
    GameWorld& world;
public:
    explicit Weapon(GameWorld& world);
    void fire_proyectil(b2Vec2 pos, float angle);

};
#endif //WORMS_SERVER_WEAPON_H
