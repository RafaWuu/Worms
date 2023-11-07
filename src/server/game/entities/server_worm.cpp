//
// Created by xguss on 02/11/23.
//

#include "server_worm.h"

#include "game/states/server_state_enum.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_error.h"

Worm::Worm(uint8_t id, b2World* b2world, float pos_x, float pos_y):
        id(id),
        client_id(),
        pos_x(pos_x),
        pos_y(pos_y),
        health(100),
        state_manager(Alive | Standing),
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
}

void Worm::set_client_id(uint16_t id_) { this->client_id = id_; }

void Worm::update(b2World* world) {
    if (jumpTimeout > 0)
        jumpTimeout--;

    getLog().write("Gusano %hhu actualizandose, x: %f, y %f: \n", id, body->GetPosition().x,
                   body->GetPosition().y);


    state_manager.update(*this);
}

void Worm::handle_input(uint16_t id_, InputEnum input) {
    if (this->client_id != id_)
        throw InvalidWormIdGameError(id);

    switch (input) {
        case Left:
            facing_right = false;
            state_manager.try_activate(StateEnum::Walking, *this);

            getLog().write("Gusano %hhu, jugador avanza a la izquierda\n", id);

            break;
        case Right:
            facing_right = true;
            state_manager.try_activate(StateEnum::Walking, *this);

            getLog().write("Gusano %hhu, jugador avanza  a la derecha\n", id);

            break;
        case Stop:
            state_manager.try_activate(StateEnum::Standing, *this);

            getLog().write("Gusano %hhu, jugador frenando\n", id);
            break;
        case JumpF:
            state_manager.try_activate(StateEnum::Jumping, *this);
            getLog().write("Gusano %hhu,jugador  saltando\n", id);

            break;
        case JumpB:
            state_manager.try_activate(StateEnum::Rolling, *this);
            getLog().write("Gusano %hhu, jugador dando una vuelta\n", id);

            break;
    }
}

ObjectType Worm::get_id() { return WORM; }

uint16_t Worm::get_state() const { return state_manager.current; }
