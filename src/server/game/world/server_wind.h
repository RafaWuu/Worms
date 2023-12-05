

#ifndef WORMS_SERVER_WIND_H
#define WORMS_SERVER_WIND_H

#include <random>

#include "../projectiles/server_projectile.h"

class Wind {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
    std::uniform_int_distribution<> dis_bool;

public:
    Wind();
    void update_wind();

    void affect_projectile(b2Body& body);

    float wind;
};
#endif  // WORMS_SERVER_WIND_H
