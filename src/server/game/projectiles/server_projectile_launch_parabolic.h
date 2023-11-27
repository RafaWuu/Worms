//
// Created by xguss on 27/11/23.
//

#ifndef WORMS_SERVER_PROJECTILE_LAUNCH_PARABOLIC_H
#define WORMS_SERVER_PROJECTILE_LAUNCH_PARABOLIC_H

#include "server_projectile_launch.h"

class ProjectileLaunchParabolic: public ProjectileLaunch {
private:
    b2Vec2 pos;
    float angle;
    float power;
    float max_vel;

public:
    ProjectileLaunchParabolic(b2Vec2 pos, float angle, float power, float max_vel);

    void execute(b2Body& body) override;
};
#endif  // WORMS_SERVER_PROJECTILE_LAUNCH_PARABOLIC_H
