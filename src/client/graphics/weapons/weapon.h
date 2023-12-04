#ifndef _WEAPONS_WEAPON_H
#define _WEAPONS_WEAPON_H

#include "../texture_controller.h"

class Weapon {
private:
public:
    // Devuelve que textura elegir cuando el gusano no se esta moviendo
    virtual AnimationState get_idle_texture_state() = 0;

    virtual AnimationState get_aiming_texture_state() = 0;

    virtual AnimationState get_projectile_texture() = 0;

    virtual bool projectile_should_loop();
    
    virtual ~Weapon() {}
};

#endif
