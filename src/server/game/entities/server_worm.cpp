//
// Created by xguss on 02/11/23.
//

#include "server_worm.h"

#include <chrono>

Worm::Worm(uint8_t id, b2Body* body): id(id), body(body), client_id(), move_state(Stop) {}

void Worm::set_client_id(uint16_t id_) { this->client_id = id_; }

void Worm::update(b2World* world) {
    b2Vec2 vel = body->GetLinearVelocity();

    if (remaining_jumpingf_steps > 0) {
        body->ApplyForce(b2Vec2(15, 45), body->GetWorldCenter(), false);
        remaining_jumpingf_steps--;
        return;
    }

    if (remaining_jumpingb_steps > 0) {
        body->ApplyForce(b2Vec2(-25, 30), body->GetWorldCenter(), false);
        remaining_jumpingb_steps--;
        return;
    }

    switch (move_state) {
        case Left:
            desiredXVel = -10;
            break;
        case Right:
            desiredXVel = 10;
            break;
        case Stop:
            desiredXVel = 0;
            break;
        case JumpB:
            remaining_jumpingb_steps = 45;
            move_state = Stop;
            break;
        case JumpF:
            remaining_jumpingf_steps = 45;
            move_state = Stop;


            break;
    }

    float velChange_x = desiredXVel - vel.x;

    float impulse_x = body->GetMass() * velChange_x;

    body->ApplyLinearImpulse(b2Vec2(impulse_x, 0), body->GetWorldCenter(), false);
}

void Worm::set_movement(uint16_t id_, MovementEnum move) {
    if (this->client_id != id_)
        return;
    this->move_state = move;
}
