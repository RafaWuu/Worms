#include "weapon.h"

class Dynamite : public Weapon {
public:
    AnimationState get_idle_texture_state() override;
    
    AnimationState get_aiming_texture_state() override;

    AnimationState get_projectile_texture() override;

    bool projectile_should_loop() override;
};
