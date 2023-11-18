//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_WORM_H
#define WORMS_SERVER_WORM_H

#include <memory>
#include <utility>
#include <vector>

#include "game/server_inputs.h"
#include "game/states/server_state_manager.h"
#include "game/world/server_gameworld.h"

#include "b2_body.h"
#include "server_gameobject.h"

class StateManager;
class Weapon;

class Worm: public GameObject {
private:
    uint16_t id;
    uint16_t client_id;

    float pos_x;
    float pos_y;


    uint8_t health;

    StateManager state_manager;

public:
    friend class WormInfo;
    friend class WormSensor;

    int numFootContacts;
    int jumpTimeout;
    float aim_power;

    Worm(uint8_t id, b2World* b2world, float pos_x, float pos_y, Weapon& weapon);
    Worm(const Worm&) = delete;
    Worm& operator=(const Worm&) = delete;

    void set_client_id(uint16_t id_);

    void update(b2World& world) override;


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
    Weapon& current_gun;
    float desiredAngle;

    void get_hit(float d);
};
#endif  // WORMS_SERVER_WORM_H
