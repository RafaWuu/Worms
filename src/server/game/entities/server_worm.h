//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_WORM_H
#define WORMS_SERVER_WORM_H

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "../../../../configuration/configuration.h"
#include "game/server_inputs.h"
#include "game/states/server_state_manager.h"
#include "game/weapons/server_weapon_info.h"

#include "b2_body.h"
#include "server_gameobject.h"

class StateManager;
class Weapon;
class GameWorld;

class Worm: public GameObject {
private:
    uint16_t client_id;

    StateManager state_manager;
    Configuration& config;

public:
    friend class WormInfo;
    friend class WormSensor;

    Worm(uint8_t id, GameWorld& world, float pos_x, float pos_y);
    Worm(const Worm&) = delete;
    Worm& operator=(const Worm&) = delete;

    uint16_t id;

    std::map<uint8_t, std::unique_ptr<Weapon>> weapons_map;

    b2Body* body;
    int numFootContacts;
    int jumpTimeout;
    bool facing_right;
    float aim_x;
    float aim_y;
    uint8_t current_weapon;
    uint8_t health;
    uint8_t recent_health;

    float recent_speed;
    bool had_used_weapon;

    void set_client_id(uint16_t id_);

    void update(GameWorld& world) override;

    std::unique_ptr<GameObjectInfo> get_status() const override;

    ObjectType get_id() const override;

    std::unique_ptr<WormInfo> get_worminfo() const;

    std::unique_ptr<WeaponInfo> get_current_weapon_info() const;

    uint16_t get_state() const;

    bool validate_client(uint16_t id_) const;

    void move(MoveDir direction);

    void jump();

    void roll_back();

    void stop_move();

    void fire();

    void stop_aim();

    void power();

    void stop_power();

    void aim(float x, float y);

    void get_hit(float d);

    void process_fall(float distance);

    void change_weapon(uint8_t weapon_id);

    void set_active();

    void set_deactive();

    void clear_attributes();
};
#endif  // WORMS_SERVER_WORM_H
