#include "configuration.h"

#include <iostream>
#include <string>

Configuration& Configuration::get_instance() {
    static Configuration instance;
    return instance;
}

Configuration::Configuration() {
    try {
        YAML::Node config = YAML::LoadFile("../configuration/configuration.yaml");

        fps = config["fps"].as<float>();
        load_weapon_info(config);
        load_server_states_info(config);

    } catch (const YAML::Exception& e1) {
        try {
            YAML::Node config = YAML::LoadFile("configuration/configuration.yaml");

            fps = config["fps"].as<float>();
            load_weapon_info(config);
            load_server_states_info(config);

        } catch (const YAML::Exception& e2) {
            // If both attempts fail, print the error messages
            std::cerr << "Error yaml: " << e1.what() << std::endl;
            std::cerr << "Error yaml: " << e2.what() << std::endl;
        }
    }
}

double Configuration::get_fps() { return fps; }

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

        int id = weapon_node["id"].as<int>();
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
                               affected_by_wind, id, ammo, damage, radius, main_explosion_damage,
                               main_explosion_radius, fragment_damage, fragment_radius,
                               fragment_number);

        weapons_info[weapon_name] = weapon_info;
    }
}

void Configuration::load_server_states_info(YAML::Node config) {
    YAML::Node states = config["server"]["states"];

    walking_velocity = states["walking"]["velocity"].as<float>();
    standing_stop_rate = states["standing"]["rate"].as<float>();

    jumping_remaining_frames = states["jumping"]["remaining_frames"].as<int>();
    jumping_jump_timeout = states["jumping"]["jump_timeout"].as<int>();
    jumping_delta_x = states["jumping"]["delta_x"].as<float>();
    jumping_delta_y = states["jumping"]["delta_y"].as<float>();

    rolling_remaining_frames = states["rolling"]["remaining_frames"].as<int>();
    rolling_jump_timeout = states["rolling"]["jump_timeout"].as<int>();
    rolling_delta_x = states["rolling"]["delta_x"].as<float>();
    rolling_delta_y = states["rolling"]["delta_y"].as<float>();

    falling_jump_timeout = states["falling"]["jump_timeout"].as<int>();

    firing_source_x = states["firing"]["offset_x"].as<float>();
    firing_source_y = states["firing"]["offset_y"].as<float>();

    powering_modifier = states["powering"]["seconds"].as<float>();
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

int Configuration::get_weapon_id(const std::string& weapon_name) {
    return weapons_info[weapon_name].id;
}

int Configuration::get_weapon_ammo(const std::string& weapon_name) {
    return weapons_info[weapon_name].ammo;
}

int Configuration::get_weapon_damage(const std::string& weapon_name) {
    return weapons_info[weapon_name].damage;
}

int Configuration::get_weapon_radius(const std::string& weapon_name) {
    return weapons_info[weapon_name].radius;
}

int Configuration::get_weapon_main_explosion_damage(const std::string& weapon_name) {
    return weapons_info[weapon_name].main_explosion_damage;
}

int Configuration::get_weapon_main_explosion_radius(const std::string& weapon_name) {
    return weapons_info[weapon_name].main_explosion_radius;
}

int Configuration::get_weapon_fragment_damage(const std::string& weapon_name) {
    return weapons_info[weapon_name].fragment_damage;
}

int Configuration::get_weapon_fragment_radius(const std::string& weapon_name) {
    return weapons_info[weapon_name].fragment_radius;
}

int Configuration::get_weapon_fragment_number(const std::string& weapon_name) {
    return weapons_info[weapon_name].fragment_number;
}

/* SERVER STATES */

// Walking
float Configuration::get_walking_velocity() const { return walking_velocity; }

// Standing
float Configuration::get_standing_stopping_rate() const { return standing_stop_rate; }

// Jumping
int Configuration::get_jumping_remaining_frames() const { return jumping_remaining_frames; }
int Configuration::get_jumping_jump_timeout() const { return jumping_jump_timeout; }
float Configuration::get_jumping_delta_x() const { return jumping_delta_x; }
float Configuration::get_jumping_delta_y() const { return jumping_delta_y; }

// Rolling
int Configuration::get_rolling_remaining_frames() const { return rolling_remaining_frames; }
int Configuration::get_rolling_jump_timeout() const { return rolling_jump_timeout; }
float Configuration::get_rolling_delta_x() const { return rolling_delta_x; }
float Configuration::get_rolling_delta_y() const { return rolling_delta_y; }

// Falling
int Configuration::get_falling_jump_timeout() const { return falling_jump_timeout; }

// Firing
float Configuration::get_firing_source_x() const { return firing_source_x; }
float Configuration::get_firing_source_y() const { return firing_source_y; }

// Powering
float Configuration::get_powering_time() const { return powering_modifier; }
