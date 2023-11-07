//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_WORM_H
#define WORMS_SERVER_WORM_H

#include <vector>

#include "game/server_move.h"
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
    uint8_t health;
    StateManager state_manager;

public:
    friend class WormInfo;
    friend class WormSensor;

    int numFootContacts;
    int jumpTimeout;

    Worm(uint8_t id, b2World* b2world, float pos_x, float pos_y);

    void set_client_id(uint16_t id_);

    void update(b2World* world);

    void handle_input(uint16_t id_, InputEnum input);

    b2Body* body;

    ObjectType get_id() override;

    bool facing_right = true;

    uint16_t get_state() const;
};
#endif  // WORMS_SERVER_WORM_H
