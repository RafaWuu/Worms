//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_WORM_H
#define WORMS_SERVER_WORM_H

#include <vector>

#include "game/server_inputs.h"
#include "game/states/server_state_manager.h"

#include "b2_body.h"
#include "server_gameobject.h"

class StateManager;

class Worm: public GameObject {
private:
    uint8_t id;
    uint16_t client_id;

    float pos_x;
    float pos_y;


    void* current_gun;

    uint8_t health;
    StateManager state_manager;

public:
    friend class WormInfo;
    friend class WormSensor;

    int numFootContacts;
    int jumpTimeout;
    float aim_angle;
    float aim_power;

    Worm(uint8_t id, b2World* b2world, float pos_x, float pos_y);

    void set_client_id(uint16_t id_);

    void update(b2World* world);


    b2Body* body;

    ObjectType get_id() override;

    bool facing_right = true;

    uint16_t get_state() const;

    void roll_back();

    void jump();

    void move(MoveDir direction);

    bool validate_client(uint16_t id_) const;

    void stop_move();

    void fire();

    void stop_aim();

    void power(bool increasing);

    void stop_power();

    bool aiming_up;
    bool increasing_power;

    void aim(float x, float y);

    float aim_x;
};
#endif  // WORMS_SERVER_WORM_H
