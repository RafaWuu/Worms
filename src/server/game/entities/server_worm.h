//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_WORM_H
#define WORMS_SERVER_WORM_H

#include <map>
#include <memory>
#include <utility>
#include <vector>

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
    uint16_t id;
    uint16_t client_id;

    float pos_x;
    float pos_y;

    StateManager state_manager;

public:
    std::map<uint8_t, std::unique_ptr<Weapon>> weapons_map;
    friend class WormInfo;
    friend class WormSensor;

    int numFootContacts;
    int jumpTimeout;
    float aim_power;

    Worm(uint8_t id, GameWorld& world, float pos_x, float pos_y);
    ~Worm();
    Worm(const Worm&) = delete;
    Worm& operator=(const Worm&) = delete;

    void set_client_id(uint16_t id_);

    void update(GameWorld& world) override;

    b2Body* body;

    ObjectType get_id() const override;

    bool facing_right = true;

    uint16_t get_state() const;

    void roll_back();

    void jump();

    void move(MoveDir direction);

    bool validate_client(uint16_t id_) const;

    void stop_move();

    void fire();

    void stop_aim();

    void power();

    void stop_power();

    bool increasing_power;

    void aim(float x, float y);

    float aim_x;
    float aim_y;

    std::unique_ptr<GameObjectInfo> get_status() const override;
    std::unique_ptr<WormInfo> get_worminfo() const;
    uint8_t ammo;
    uint8_t current_weapon;
    float desiredAngle;

    void get_hit(float d);

    void process_fall(float distance);

    uint8_t health;

    void change_weapon(uint8_t weapon_id);

    float get_angle();

    std::unique_ptr<WeaponInfo> get_current_weapon_info() const;
};
#endif  // WORMS_SERVER_WORM_H
