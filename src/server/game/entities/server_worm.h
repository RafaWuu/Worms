//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_WORM_H
#define WORMS_SERVER_WORM_H

#include "game/server_move.h"

#include "b2_body.h"
#include "server_gameobject.h"

class Worm: public GameObject {
private:
    uint8_t id;
    uint16_t client_id;

    float pos_x;
    float pos_y;
    int8_t health;

    MovementEnum move_state;
    b2Body* body;

    int remaining_jumpingf_steps;
    int remaining_jumpingb_steps;
    float desiredXVel;
    int numFootContacts;
    int jumpTimeout;

public:
    friend class WormInfo;
    friend class WormSensor;

    Worm(uint8_t id, b2World* b2world, float pos_x, float pos_y);

    void set_client_id(uint16_t id_);

    void update(b2World* world);

    void set_movement(uint16_t id_, MovementEnum move);

    ObjectType get_id() override;
};
#endif  // WORMS_SERVER_WORM_H
