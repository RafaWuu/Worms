

#ifndef WORMS_SERVER_PROJECTILE_LAUNCH_H
#define WORMS_SERVER_PROJECTILE_LAUNCH_H

#include "box2d/b2_body.h"

class ProjectileLaunch {
public:
    virtual ~ProjectileLaunch() = default;
    virtual void execute(b2Body& body) = 0;
};

#endif  // WORMS_SERVER_PROJECTILE_LAUNCH_H
