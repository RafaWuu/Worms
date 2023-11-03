//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_WORM_H
#define WORMS_SERVER_WORM_H

#include "b2_body.h"
#include "server_move.h"

class Worm {
private:
    MovementEnum move_state;
    uint16_t client_id;
    uint8_t id;
    int8_t health = 100;
    b2Body* body;

    int remaining_jumpingf_steps = 0;
    int remaining_jumpingb_steps = 0;
    float desiredXVel = 0;

public:
    friend class WormInfo;

    explicit Worm(uint8_t id, b2Body* body);

    void set_client_id(uint16_t id_);

    void update(b2World* world);

    void set_movement(uint16_t id_, MovementEnum move);
};
#endif  // WORMS_SERVER_WORM_H
