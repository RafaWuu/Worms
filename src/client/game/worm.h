#ifndef WORM_H
#define WORM_H

#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "entity_info.h"
#include "aim_info.h"

enum WORM_STATE { DirLeft = 1, DirRight = 2, Stop = 3, JumpF = 4, JumpB = 5 };

class Worm: public EntityInfo {
private:
    uint16_t id;
    uint16_t ammo;

    uint8_t dir;
    uint16_t state;
    uint8_t health;
    uint8_t current_weapon;
    AimInfo aim_info;
    uint8_t attack_power;

public:
    Worm(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height, uint8_t dir,
         uint16_t state, uint8_t health, uint8_t current_weapon, uint16_t ammo,  
         uint8_t attack_power, AimInfo aim_info);

    Worm(uint16_t id, uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height, uint8_t dir,
         uint16_t state, uint8_t health, uint8_t current_weapon);

    void set_position(float x, float y);
    void set_health(int8_t health);

    int get_health();
    int get_state();
    int get_ammo();
    uint16_t get_id() const override;

    uint8_t get_dir() const;

    uint8_t get_current_weapon();

    float get_aim_angle();
    float get_x_aim();
    float get_y_aim();
    AimInfo get_aim_info();

    uint8_t get_attack_power();

    std::unique_ptr<Entity> create(TextureController& controller) override;
};

#endif
