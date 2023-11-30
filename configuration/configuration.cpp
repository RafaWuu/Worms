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
        tick_rate = config["tick_rate"].as<float>();
        bg_music_distance = config["bg_music_distance"].as<int>();
        sound_effect_distance = config["sound_effect_distance"].as<int>();

        load_weapon_info(config);
        load_server_states_info(config);
        load_entities_info(config);

    } catch (const YAML::Exception& e1) {
        try {
            YAML::Node config = YAML::LoadFile("configuration/configuration.yaml");

            fps = config["fps"].as<float>();
            tick_rate = config["tick_rate"].as<float>();
            bg_music_distance = config["bg_music_distance"].as<int>();
            sound_effect_distance = config["sound_effect_distance"].as<int>();

            load_weapon_info(config);
            load_server_states_info(config);
            load_entities_info(config);
        } catch (const YAML::Exception& e2) {
            // If both attempts fail, print the error messages
            std::cerr << "Error yaml: " << e1.what() << std::endl;
            std::cerr << "Error yaml: " << e2.what() << std::endl;
        }
    }

}

int Configuration::get_sound_effect_distance() { return sound_effect_distance; }
int Configuration::get_bg_music_distance() { return bg_music_distance; }

double Configuration::get_fps() { return fps; }
double Configuration::get_tick_rate() { return tick_rate; }

void Configuration::load_entities_info(YAML::Node config) {
    auto worm_node = config["worm"];

    worm_width = worm_node["width"].as<float>();
    worm_height = worm_node["height"].as<float>();
    worm_health = worm_node["health"].as<int>();
    max_fall_dmg = worm_node["max_fall_dmg"].as<int>();
    safe_height = worm_node["safe_height"].as<int>();
    restitution = worm_node["restitution"].as<float>();
    density = worm_node["density"].as<float>();
    friction = worm_node["friction"].as<float>();

    auto beam_node = config["beam"];

    beam_large_width = beam_node["large_width"].as<float>();
    beam_small_width = beam_node["small_width"].as<float>();
    beam_height = beam_node["height"].as<float>();
}

void Configuration::load_weapon_info(YAML::Node config) {
    maximum_countdown = config["maximum_countdown"].as<float>();
    round_length = config["round_length"].as<float>();
    grace_length = config["grace_length"].as<float>();

    for (const auto& weapon: config["weapons"]) {
        auto weapon_name = weapon.first.as<std::string>();
        const YAML::Node& weapon_node = weapon.second;

        WeaponConfig weapon_info(weapon.second);

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

std::string Configuration::get_weapon_name(int id) {
    auto w = std::find_if(weapons_info.begin(), weapons_info.end(),
                          [id](const auto& weapon) { return weapon.second.id == id; });

    if (w != weapons_info.end())
        return w->first;

    throw YAML::Exception::exception();  // TODO mejorar ?)
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

float Configuration::get_weapon_width(const std::string& weapon_name) {
    return weapons_info[weapon_name].width;
}

float Configuration::get_weapon_height(const std::string& weapon_name) {
    return weapons_info[weapon_name].height;
}

float Configuration::get_weapon_blastpower(const std::string& weapon_name) {
    return weapons_info[weapon_name].blast_power;
}

float Configuration::get_weapon_dragconstant(const std::string& weapon_name) {
    return weapons_info[weapon_name].drag_constant;
}

float Configuration::get_weapon_density(const std::string& weapon_name) {
    return weapons_info[weapon_name].density;
}

float Configuration::get_weapon_damping(const std::string& weapon_name) {
    return weapons_info[weapon_name].angular_damping;
}

float Configuration::get_weapon_max_vel(const std::string& weapon_name) {
    return weapons_info[weapon_name].max_vel;
}

float Configuration::get_restitution(const std::string& weapon_name) {
    return weapons_info[weapon_name].restitution;
}

float Configuration::get_maximum_countdown() const { return maximum_countdown; }


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
