#include "configuration.h"
#include <iostream>
Configuration& Configuration::get_instance() {
    static Configuration instance;
    return instance;
}

Configuration::Configuration() { 
    try {
        YAML::Node config = YAML::LoadFile("configuration/configuration.yaml");
        load_weapon_info(config); 
        load_server_states_info(config);
    } catch (const YAML::Exception& e) {
        std::cerr << "Error yaml: " << e.what() << std::endl;
    }

}

void Configuration::load_weapon_info(YAML::Node config) {

    for (const auto& weapon: config["weapons"]) {
        std::string weapon_name = weapon.first.as<std::string>();
        const YAML::Node& weapon_node = weapon.second;

        bool scope = weapon_node["scope"].as<bool>(false);
        bool hand_to_hand = weapon_node["hand_to_hand"].as<bool>(false);
        bool variable_power = weapon_node["variable_power"].as<bool>(false);
        bool countdown = weapon_node["countdown"].as<bool>(false);
        bool point_and_click = weapon_node["point_and_click"].as<bool>(false);
        bool affected_by_wind = weapon_node["affected_by_wind"].as<bool>(false);
        int ammo = weapon_node["ammo"].as<int>();
        int damage = weapon_node["damage"].as<int>(0);
        int radius = weapon_node["radius"].as<int>(0);
        

        int main_explosion_damage = 0;
        int main_explosion_radius = 0;
        if (weapon_node["explosion"]) {
            const YAML::Node& explosion_node = weapon_node["explosion"];
            main_explosion_damage = explosion_node["damage"].as<int>();
            main_explosion_radius = explosion_node["radius"].as<int>();
        }

        int fragment_damage = 0;
        int fragment_radius = 0;
        int fragment_number = 0;
        if (weapon_node["fragment"]) {
            const YAML::Node& fragment_node = weapon_node["fragment"];
            fragment_damage = fragment_node["damage"].as<int>();
            fragment_radius = fragment_node["radius"].as<int>();
            fragment_number = weapon_node["fragment_number"].as<int>();
        }

        WeaponInfo weapon_info(scope, hand_to_hand, variable_power, countdown, point_and_click,
                               affected_by_wind, ammo, damage, radius, main_explosion_damage,
                               main_explosion_radius, fragment_damage, fragment_radius, fragment_number);

        weapons_info[weapon_name] = weapon_info;
    }
}

void Configuration::load_server_states_info(YAML::Node config) {
    YAML::Node states = config["server"]["states"];

    walking_velocity = states["walking"]["velocity"].as<float>();
    standing_velocity = states["standing"]["velocity"].as<float>();

    jumping_remaining_frames = states["jumping"]["remaining_frames"].as<int>();
    jumping_jump_timeout = states["jumping"]["jump_timeout"].as<int>();
    jumping_force_x = states["jumping"]["force_x"].as<int>();
    jumping_force_y = states["jumping"]["force_y"].as<int>();

    rolling_remaining_frames = states["rolling"]["remaining_frames"].as<int>();
    rolling_jump_timeout = states["rolling"]["jump_timeout"].as<int>();
    rolling_force_x = states["rolling"]["force_y"].as<int>();
    rolling_force_y = states["rolling"]["force_y"].as<int>();

    falling_jump_timeout = states["falling"]["jump_timeout"].as<int>();

    firing_source_x = states["firing"]["source_x"].as<float>();
    firing_source_y = states["firing"]["source_y"].as<float>();

    powering_modifier = states["powering"]["modifier"].as<float>();   
}

bool Configuration::weapon_has_scope(const std::string& weapon_name) {
    return weapons_info[weapon_name].scope;
}

bool Configuration::weapon_is_h2h(const std::string& weapon_name) {
    return weapons_info[weapon_name].hand_to_hand;    
}

bool Configuration::weapon_has_variable_power(const std::string& weapon_name) {
    return weapons_info[weapon_name].variable_power;    
}

bool Configuration::weapon_has_countdown(const std::string& weapon_name) {
    return weapons_info[weapon_name].countdown;    
}

bool Configuration::weapon_is_point_and_click(const std::string& weapon_name) {
    return weapons_info[weapon_name].point_and_click;    
}

bool Configuration::weapon_is_affected_by_wind(const std::string& weapon_name) {
    return weapons_info[weapon_name].affected_by_wind;    
}

int Configuration::weapon_ammo(const std::string& weapon_name) {
    return weapons_info[weapon_name].ammo;    
}

int Configuration::weapon_damage(const std::string& weapon_name) {
    return weapons_info[weapon_name].damage;    
}

int Configuration::weapon_radius(const std::string& weapon_name) {
    return weapons_info[weapon_name].radius;    
}

int Configuration::weapon_main_explosion_damage(const std::string& weapon_name) {
    return weapons_info[weapon_name].main_explosion_damage;    
}

int Configuration::weapon_main_explosion_radius(const std::string& weapon_name) {
    return weapons_info[weapon_name].main_explosion_radius;    
}

int Configuration::weapon_fragment_damage(const std::string& weapon_name) {
    return weapons_info[weapon_name].fragment_damage;    
}

int Configuration::weapon_fragment_radius(const std::string& weapon_name) {
    return weapons_info[weapon_name].fragment_radius;    
}

int Configuration::weapon_fragment_number(const std::string& weapon_name) {
    return weapons_info[weapon_name].fragment_number;    
}

/* SERVER STATES */

// Walking
float Configuration::get_walking_velocity() const{ 
    return walking_velocity;
}

// Standing
float Configuration::get_standing_velocity() const {
    return standing_velocity;
}

// Jumping
int Configuration::get_jumping_remaining_frames() const {
    return jumping_remaining_frames;
}
int Configuration::get_jumping_jump_timeout() const {
    return jumping_jump_timeout;
}
int Configuration::get_jumping_force_x() const {
    return jumping_force_x;
}
int Configuration::get_jumping_force_y() const {
    return jumping_force_y;
}

// Rolling
int Configuration::get_rolling_remaining_frames() const {
    return rolling_remaining_frames;
}
int Configuration::get_rolling_jump_timeout() const {
    return rolling_jump_timeout;
}
int Configuration::get_rolling_force_x() const {
    return rolling_force_x;
}
int Configuration::get_rolling_force_y() const {
    return rolling_force_y;
}

// Falling
int Configuration::get_falling_jump_timeout() const {
    return falling_jump_timeout;
}

// Firing
float Configuration::get_firing_source_x() const {
    return firing_source_x;
}
float Configuration::get_firing_source_y() const {
    return firing_source_y;
}

// Powering
float Configuration::get_powering_modifier() const {
    return powering_modifier;
}