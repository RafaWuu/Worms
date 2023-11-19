#ifndef _WEAPON_INFO_H_
#define _WEAPON_INFO_H_

#include "configuration.h"

class WeaponInfo {
    bool scope;
    bool hand_to_hand;
    bool variable_power;
    bool countdown;
    bool point_and_click;
    bool affected_by_wind;
    int ammo;
    int damage;
    int radius;
    int main_explosion_damage;
    int main_explosion_radius;
    int fragment_damage;
    int fragment_radius;
    int fragment_number;

public:
    friend class Configuration;

    WeaponInfo() = default;

    WeaponInfo(bool scope, bool hand_to_hand, bool variable_power, bool countdown,
               bool point_and_click, bool affected_by_wind, int ammo, int damage, int radius,
               int main_explosion_damage, int main_explosion_radius, int fragment_damage, int fragment_radius,
               int fragment_number);
};

#endif
