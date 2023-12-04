#ifndef _WEAPON_INFO_H_
#define _WEAPON_INFO_H_

#include "configuration.h"

class WeaponConfig {
    bool scope;
    bool hand_to_hand;
    bool variable_power;
    bool countdown;
    bool point_and_click;
    bool affected_by_wind;

    int id;
    int ammo;
    int damage;
    int radius;
    int main_explosion_damage;
    int main_explosion_radius;
    int fragment_damage;
    int fragment_radius;
    int fragment_number;

    float width;
    float height;
    float blast_power;
    float drag_constant;
    float density;
    float angular_damping;
    float max_vel;
    int quantity;

public:
    friend class Configuration;

    WeaponConfig() = default;

    explicit WeaponConfig(const YAML::Node& weapon_node);

    float restitution;
};

#endif
