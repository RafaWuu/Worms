//
// Created by xguss on 02/11/23.
//

#include "server_worm.h"

#include <chrono>

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_error.h"

Worm::Worm(uint8_t id, b2World* b2world, float pos_x, float pos_y):
        id(id),
        client_id(),
        pos_x(pos_x),
        pos_y(pos_y),
        health(100),
        move_state(Stop),
        GameObject() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos_x, pos_y);

    body = b2world->CreateBody(&bodyDef);
    body->SetFixedRotation(true);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .3f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;

    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    body->CreateFixture(&fixtureDef);

    getLog().write("Creando gusano %hhu, x: %f, y %f: \n", id, pos_x, pos_y);

    numFootContacts = 0;
    remaining_jumpingb_steps = 0;
    remaining_jumpingf_steps = 0;
}

void Worm::set_client_id(uint16_t id_) { this->client_id = id_; }

void Worm::update(b2World* world) {
    if (jumpTimeout > 0)
        jumpTimeout--;

    if (remaining_jumpingf_steps > 0) {
        body->ApplyForce(b2Vec2(15, 25), body->GetWorldCenter(), true);
        remaining_jumpingf_steps--;
        return;
    }

    if (remaining_jumpingb_steps > 0) {
        body->ApplyForce(b2Vec2(-25, 15), body->GetWorldCenter(), true);
        remaining_jumpingb_steps--;
        return;
    }

    b2Vec2 vel = body->GetLinearVelocity();
    getLog().write("Actualizando Gusano %hhu, su velocidad es%f %f\n", id, vel.x, vel.y);

    switch (move_state) {
        case Left:
            desiredXVel = -.2;
            getLog().write("Gusano %hhu, moviendo a la izquierda\n", id);

            break;
        case Right:
            desiredXVel = .2;
            getLog().write("Gusano %hhu, moviendo a la derecha\n", id);

            break;
        case Stop:
            desiredXVel = vel.x * 0.990f;
            getLog().write("Gusano %hhu, frenando\n", id);

            break;
        case JumpB:
            remaining_jumpingb_steps = 6;
            jumpTimeout = 15;
            this->move_state = Stop;
            getLog().write("Gusano %hhu, iniciando salto\n", id);

            break;
        case JumpF:
            remaining_jumpingf_steps = 6;
            jumpTimeout = 15;
            this->move_state = Stop;
            getLog().write("Gusano %hhu, iniciando salto hacia atras\n", id);

            break;
    }

    float velChange_x = desiredXVel - vel.x;

    float impulse_x = body->GetMass() * velChange_x;

    getLog().write("Gusano %hhu, aplicando impulso %f %f\n", id, impulse_x, 0);

    body->ApplyLinearImpulse(b2Vec2(impulse_x, 0), body->GetWorldCenter(), true);
}

void Worm::set_movement(uint16_t id_, MovementEnum move) {
    if (this->client_id != id_)
        throw InvalidWormIdGameError(id);

    switch (move_state) {

        case Left:
            if (remaining_jumpingb_steps > 0 || remaining_jumpingf_steps > 0)
                return;

            if (move == JumpB || move == JumpF) {

                if (jumpTimeout > 0)
                    return;
            }
            getLog().write("Gusano %hhu, cambiando estado a %hhu\n", id, move);

            move_state = move;
            break;
        case Right:
            if (remaining_jumpingb_steps > 0 || remaining_jumpingf_steps > 0)
                return;
            if (move == JumpB || move == JumpF) {
                if (numFootContacts < 1)
                    return;
                if (jumpTimeout > 0)
                    return;
            }
            getLog().write("Gusano %hhu, cambiando estado a %hhu\n", id, move);

            move_state = move;
            break;
        case Stop:
            if (remaining_jumpingb_steps > 0 || remaining_jumpingf_steps > 0)
                return;

            if (move == JumpB || move == JumpF) {
                if (numFootContacts < 1)
                    return;
                if (jumpTimeout > 0)
                    return;
            }

            getLog().write("Gusano %hhu, cambiando estado a %hhu\n", id, move);
            move_state = move;

            break;
        case JumpF:
            break;
        case JumpB:
            break;
    }
}

ObjectType Worm::get_id() { return WORM; }
