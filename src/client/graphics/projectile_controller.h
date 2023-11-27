#ifndef _CLIENT_PROJECTILE_CONTROLLER_H
#define _CLIENT_PROJECTILE_CONTROLLER_H

#include "../../configuration/configuration.h"

#include "common_weapon_constants.h"
#include "texture_controller.h"

// Poner esto directamente en TextureController?
class ProjectileController {
public:
    AnimationState get_projectile_texture(uint8_t projectile_id);
};

#endif
