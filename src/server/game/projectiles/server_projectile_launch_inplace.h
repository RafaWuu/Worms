//
// Created by xguss on 27/11/23.
//

#ifndef WORMS_SERVER_PROJECTILE_LAUNCH_INPLACE_H
#define WORMS_SERVER_PROJECTILE_LAUNCH_INPLACE_H


#include "server_projectile_launch.h"

class ProjectileLaunchInPlace: public ProjectileLaunch {
private:
    b2Vec2 pos;
    float max_vel;

public:
    ProjectileLaunchInPlace(b2Vec2 pos, float max_vel);

    void execute(b2Body& body) override;
};

#endif  // WORMS_SERVER_PROJECTILE_LAUNCH_INPLACE_H
