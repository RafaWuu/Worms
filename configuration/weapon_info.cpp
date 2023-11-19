#include "weapon_info.h"

WeaponInfo::WeaponInfo(bool scope, bool hand_to_hand, bool variable_power, bool countdown,
                       bool point_and_click, bool affected_by_wind, int ammo, int damage,
                       int radius, int main_explosion_damage, int main_explosion_radius, int fragment_damage,
                       int fragment_radius, int fragment_number):
        scope(scope),
        hand_to_hand(hand_to_hand),
        variable_power(variable_power),
        countdown(countdown),
        point_and_click(point_and_click),
        affected_by_wind(affected_by_wind),
        ammo(ammo),
        damage(damage),
        radius(radius),
        main_explosion_damage(main_explosion_damage),
        main_explosion_radius(main_explosion_radius),
        fragment_damage(fragment_damage),
        fragment_radius(fragment_radius),
        fragment_number(fragment_number) {}