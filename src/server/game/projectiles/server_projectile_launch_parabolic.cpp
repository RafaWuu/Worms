//
// Created by xguss on 27/11/23.
//

#include "server_projectile_launch_parabolic.h"

#include "server_projectile_launch_inplace.h"


ProjectileLaunchParabolic::ProjectileLaunchParabolic(b2Vec2 pos, float angle, float power,
                                                     float max_vel) {
    this->pos = pos;
    this->angle = angle;
    this->power = power;
    this->max_vel = max_vel;
}

void ProjectileLaunchParabolic::execute(b2Body& body) {
    body.SetTransform(pos, angle);
    body.SetLinearVelocity(body.GetWorldVector(b2Vec2(power * max_vel, 0)));
}
