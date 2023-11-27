#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <map>
#include <string>

#include "yaml-cpp/yaml.h"

#include "weapon_info.h"

class WeaponConfig;

/**
 * Ejemplo:
 *
 * Configuration& config = Configuration::get_instance();
 * bool has_scope = config.weapon_has_scope("bazooka");
 *
 */

// Singleton
class Configuration {
private:
    double fps;
    double tick_rate;

    float walking_velocity;
    float standing_stop_rate;

    int jumping_remaining_frames;
    int jumping_jump_timeout;
    float jumping_delta_x;
    float jumping_delta_y;

    int rolling_remaining_frames;
    int rolling_jump_timeout;
    float rolling_delta_x;
    float rolling_delta_y;

    int falling_jump_timeout;

    float firing_source_x;
    float firing_source_y;

    float powering_modifier;
    float maximum_countdown;
    Configuration();

    ~Configuration() = default;

    Configuration(const Configuration&) = delete;

    Configuration& operator=(const Configuration&) = delete;

    void load_weapon_info(YAML::Node config);
    void load_server_states_info(YAML::Node config);

public:
    std::map<std::string, WeaponConfig> weapons_info;

    static Configuration& get_instance();

    double get_fps();
    double get_tick_rate();

    /* WEAPONS INFO */

    bool weapon_has_scope(const std::string& weapon_name);
    // hand to hand / cuerpo a cuerpo
    bool weapon_is_h2h(const std::string& weapon_name);
    // weapon can be powered up
    bool weapon_has_variable_power(const std::string& weapon_name);
    bool weapon_has_countdown(const std::string& weapon_name);
    // teledirigido, no need to aim
    bool weapon_is_point_and_click(const std::string& weapon_name);
    bool weapon_is_affected_by_wind(const std::string& weapon_name);

    // returns -1 if ammo is infinite
    int get_weapon_ammo(const std::string& weapon_name);
    std::string get_weapon_name(int id);

    int get_weapon_id(const std::string& weapon_name);
    // returns 0 if weapon has main a explosion & fragments, you need to check their respective
    // damages
    int get_weapon_damage(const std::string& weapon_name);
    // returns 0 if weapon has main a explosion & fragments, you need to check their respective
    // radiuses
    int get_weapon_radius(const std::string& weapon_name);
    // returns 0 if there's no explosion
    int get_weapon_main_explosion_damage(const std::string& weapon_name);
    // returns 0 if there's no explosion
    int get_weapon_main_explosion_radius(const std::string& weapon_name);
    // returns 0 if there's no explosion/fragments
    int get_weapon_fragment_damage(const std::string& weapon_name);
    // returns 0 if there's no explosion/fragments
    int get_weapon_fragment_radius(const std::string& weapon_name);
    int get_weapon_fragment_number(const std::string& weapon_name);

    float get_weapon_width(const std::string& weapon_name);
    float get_weapon_height(const std::string& weapon_name);
    float get_weapon_blastpower(const std::string& weapon_name);
    float get_weapon_dragconstant(const std::string& weapon_name);
    float get_weapon_density(const std::string& weapon_name);
    float get_weapon_damping(const std::string& weapon_name);
    float get_weapon_max_vel(const std::string& weapon_name);


    /* SERVER STATES */

    float get_walking_velocity() const;
    // Velocity modifier when worm stops moving
    float get_standing_stopping_rate() const;

    int get_jumping_remaining_frames() const;
    int get_jumping_jump_timeout() const;
    float get_jumping_delta_x() const;
    float get_jumping_delta_y() const;

    int get_rolling_remaining_frames() const;
    int get_rolling_jump_timeout() const;
    float get_rolling_delta_x() const;
    float get_rolling_delta_y() const;

    int get_falling_jump_timeout() const;

    float get_firing_source_x() const;
    float get_firing_source_y() const;

    // Aim power modifier
    float get_powering_time() const;

    int getFps() const { return fps; }

    float get_maximum_countdown() const;
};

#endif
