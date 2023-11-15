//
// Created by xguss on 02/11/23.
//

#include "server_worm.h"

#include "game/states/server_state_enum.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_error.h"

#include "server_worm_info.h"

Worm::Worm(uint8_t id, b2World* b2world, float pos_x, float pos_y, Weapon& weapon):
        id(id),
        client_id(),
        pos_x(pos_x),
        pos_y(pos_y),
        health(100),
        state_manager(Alive | Standing),
        current_gun(weapon),
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
    ammo = 0;
}

void Worm::set_client_id(uint16_t id_) { this->client_id = id_; }

void Worm::update(b2World& world) {
    if (jumpTimeout > 0)
        jumpTimeout--;

    if (numFootContacts < 1)
        state_manager.try_activate(StateEnum::Falling, *this);

    //getLog().write("Gusano %hhu actualizandose, x: %f, y %f: \n", id, body->GetPosition().x,
      //             body->GetPosition().y);


    state_manager.update(*this);
}

void Worm::move(MoveDir direction) {
    if(state_manager.try_activate(StateEnum::Walking, *this)){
        facing_right = direction == DirRight;
        getLog().write("Gusano %hhu, jugador avanza a la %s\n",
                       facing_right ? "derecha" : "izquierda");
    }
}

void Worm::stop_move() {
    bool r = state_manager.try_activate(StateEnum::Standing, *this);

    if(r)
        getLog().write("Gusano %hhu, jugador frenando\n", id);
}

void Worm::jump() {
    bool r = state_manager.try_activate(StateEnum::Jumping, *this);
    if (r)
        getLog().write("Gusano %hhu,jugador  saltando\n", id);
}

void Worm::roll_back() {
    bool r =  state_manager.try_activate(StateEnum::Rolling, *this);

    if (r)
        getLog().write("Gusano %hhu, jugador dando una vuelta\n", id);
}


ObjectType Worm::get_id() const { return WORM; }

uint16_t Worm::get_state() const { return state_manager.current; }

bool Worm::validate_client(uint16_t id_) const{
    return id_ == this->client_id;
}

void Worm::fire(){
    bool r =  state_manager.try_activate(StateEnum::Firing, *this);
    if (r)
        ammo--;


}

void Worm::aim(float x, float y){
    this->aim_x = x;
    this->aim_y = y;

    getLog().write("Gusano %hhu, jugador apunta hacia %f, %f\n",
                   x, y);

    state_manager.try_activate(StateEnum::Aiming, *this);
}

void Worm::stop_aim(){
    state_manager.deactivate_states(StateEnum::Aiming, *this);
    getLog().write("Gusano %hhu, jugador deja de apuntar\n");
}

void Worm::power(bool increasing){
    if(state_manager.try_activate(StateEnum::Powering, *this)){
        increasing_power = increasing;
        getLog().write("Gusano %hhu, jugador %s su ataque\n",
                       aiming_up ? "potencia" : "des-potencia");
    }
}

void Worm::stop_power(){
    state_manager.deactivate_states(StateEnum::Powering, *this);
    getLog().write("Gusano %hhu, jugador deja de cambiar la potencia de su ataque\n");

}
std::unique_ptr<GameObjectInfo> Worm::get_status() const {
    return std::make_unique<WormInfo>(*this);
}

std::unique_ptr<WormInfo> Worm::get_worminfo() const {
    return std::make_unique<WormInfo>(*this);
}