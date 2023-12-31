

#include "server_projectile_launch_inplace.h"

ProjectileLaunchInPlace::ProjectileLaunchInPlace(b2Vec2 pos, float max_vel) {
    this->pos = pos;
    this->max_vel = max_vel;
}

void ProjectileLaunchInPlace::execute(b2Body& body) {
    body.SetTransform(pos, 0);
    body.SetLinearVelocity(body.GetWorldVector(b2Vec2(0, max_vel)));
}
