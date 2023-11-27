#include "weapon_info.h"

WeaponConfig::WeaponConfig(const YAML::Node& weapon_node) {
    scope = weapon_node["scope"].as<bool>(false);
    hand_to_hand = weapon_node["hand_to_hand"].as<bool>(false);
    variable_power = weapon_node["variable_power"].as<bool>(false);
    countdown = weapon_node["countdown"].as<bool>(false);
    point_and_click = weapon_node["point_and_click"].as<bool>(false);
    affected_by_wind = weapon_node["affected_by_wind"].as<bool>(false);

    id = weapon_node["id"].as<int>();
    ammo = weapon_node["ammo"].as<int>();
    damage = weapon_node["damage"].as<int>(0);
    radius = weapon_node["radius"].as<int>(0);


    main_explosion_damage = 0;
    main_explosion_radius = 0;

    if (weapon_node["main_explosion"]) {
        const YAML::Node& explosion_node = weapon_node["main_explosion"];
        main_explosion_damage = explosion_node["damage"].as<int>();
        main_explosion_radius = explosion_node["radius"].as<int>();
    }

    fragment_damage = 0;
    fragment_radius = 0;
    fragment_number = 0;
    if (weapon_node["fragment"]) {
        const YAML::Node& fragment_node = weapon_node["fragment"];
        fragment_damage = fragment_node["damage"].as<int>();
        fragment_radius = fragment_node["radius"].as<int>();
        fragment_number = weapon_node["fragment_number"].as<int>();
    }

    width = weapon_node["width"].as<float>();
    height = weapon_node["height"].as<float>();
    blast_power = weapon_node["blast_power"].as<float>();
    drag_constant = weapon_node["drag_constant"].as<float>();

    density = weapon_node["density"].as<float>();
    angular_damping = weapon_node["angular_damping"].as<float>();
    max_vel = weapon_node["max_vel"].as<float>();
    restitution = weapon_node["restitution"].as<float>(0.2);
}
