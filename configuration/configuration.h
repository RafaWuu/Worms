#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include "yaml-cpp/yaml.h"
#include <map>
#include "weapon_info.h"

class WeaponInfo;

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
    std::map<std::string, WeaponInfo> weapons_info;

    float walking_velocity;
    float standing_velocity;

    int jumping_remaining_frames;
    int jumping_jump_timeout;
    int jumping_force_x;
    int jumping_force_y;

    int rolling_remaining_frames;
    int rolling_jump_timeout;
    int rolling_force_x;
    int rolling_force_y;

    int falling_jump_timeout;

    float firing_source_x;
    float firing_source_y;

    float powering_modifier;

    Configuration();

    ~Configuration() = default;

    Configuration(const Configuration&) = delete;

    Configuration& operator=(const Configuration&) = delete;

    void load_weapon_info(YAML::Node config);
    void load_server_states_info(YAML::Node config);

public:
    static Configuration& get_instance();

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
    int weapon_ammo(const std::string& weapon_name);
    // returns 0 if weapon has main a explosion & fragments, you need to check their respective damages
    int weapon_damage(const std::string& weapon_name);
    // returns 0 if weapon has main a explosion & fragments, you need to check their respective radiuses
    int weapon_radius(const std::string& weapon_name);
    // returns 0 if there's no explosion
    int weapon_main_explosion_damage(const std::string& weapon_name);
    // returns 0 if there's no explosion
    int weapon_main_explosion_radius(const std::string& weapon_name);
    // returns 0 if there's no explosion/fragments
    int weapon_fragment_damage(const std::string& weapon_name);
    // returns 0 if there's no explosion/fragments
    int weapon_fragment_radius(const std::string& weapon_name);
    int weapon_fragment_number(const std::string& weapon_name);


    /* SERVER STATES */

    float get_walking_velocity() const ;
    // Velocity modifier when worm stops moving
    float get_standing_velocity() const ;
    
    int get_jumping_remaining_frames() const ;
    int get_jumping_jump_timeout() const ;
    int get_jumping_force_x() const ;
    int get_jumping_force_y() const ;
    
    int get_rolling_remaining_frames() const ;
    int get_rolling_jump_timeout() const ;
    int get_rolling_force_x() const ;
    int get_rolling_force_y() const ;
    
    int get_falling_jump_timeout() const ;
    
    float get_firing_source_x() const ;
    float get_firing_source_y() const ;
    
    // Aim power modifier
    float get_powering_modifier() const ;
};

#endif
