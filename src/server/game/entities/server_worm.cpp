//
// Created by xguss on 02/11/23.
//

#include "server_worm.h"

#include <algorithm>
#include <memory>
#include <utility>

#include "game/states/server_state_enum.h"
#include "game/weapons/server_weapon_factory.h"
#include "game/world/server_gameworld.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "common_weapon_constants.h"
#include "server_error.h"
#include "server_worm_info.h"


Worm::Worm(uint8_t id, GameWorld& world, float pos_x, float pos_y):
        id(id),
        client_id(),
        weapons_map(WeaponFactory::get_weapons(world, *this)),
        state_manager(Alive | Standing),
        config(Configuration::get_instance()),
        GameObject() {


    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos_x, pos_y);

    body = world.b2_world.CreateBody(&bodyDef);
    body->SetFixedRotation(true);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(config.worm_height / 2, config.worm_width / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    fixtureDef.filter.categoryBits = WORM;
    fixtureDef.filter.maskBits =
            BOUNDARY | projectile | PROVISION | BEAM | EXPLOSION | MELEE_SENSOR | PROVISION_SENSOR;

    fixtureDef.density = config.worm_density;
    fixtureDef.restitution = config.worm_restitution;
    fixtureDef.friction = config.worm_friction;

    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    body->CreateFixture(&fixtureDef);

    getLog().write("Creando gusano %hhu, x: %f, y %f: \n", id, pos_x, pos_y);

    facing_right = true;
    current_weapon = BAZOOKA_ID;
    health = config.worm_health;
    numFootContacts = 0;
    jumpTimeout = 0;
    aim_x = 0;
    aim_y = 0;
    recent_health = health;
    recent_speed = 0;
    had_used_weapon = false;
}

void Worm::process_fall(float distance) {
    double max = fmax(25, config.max_fall_dmg);

    if (distance > config.safe_height)
        health -= (uint8_t)fmin(distance, max);
}

void Worm::set_client_id(uint16_t id_) { this->client_id = id_; }

void Worm::update(GameWorld& world) {
    if (numFootContacts < 1)
        state_manager.try_activate(StateEnum::Falling, *this);

    bool weapon_already_used = had_used_weapon;
    // getLog().write("Gusano %hhu actualizandose, x: %f, y %f: \n", id, body->GetPosition().x,
    //              body->GetPosition().y);

    state_manager.update(*this);

    if (recent_health > health)
        world.notify_damaged_worm(this->id);

    recent_health = health;

    float speedNow = body->GetLinearVelocity().Length();
    recent_speed = 0.1 * speedNow + 0.9 * recent_speed;

    if (recent_speed > 0.05)
        world.notify_entity_is_moving();

    if (had_used_weapon && !weapon_already_used)
        world.notify_weapon_used();
}

void Worm::move(MoveDir direction) {
    if (state_manager.try_activate(StateEnum::Walking, *this)) {
        facing_right = direction == DirRight;
        getLog().write("Gusano %hhu, jugador avanza a la %s\n",
                       facing_right ? "derecha" : "izquierda");
    }
}

void Worm::stop_move() {
    bool r = state_manager.try_activate(StateEnum::Standing, *this);

    if (r)
        getLog().write("Gusano %hhu, jugador frenando\n", id);
}

void Worm::jump() {
    bool r = state_manager.try_activate(StateEnum::Jumping, *this);
    if (r)
        getLog().write("Gusano %hhu,jugador  saltando\n", id);
}

void Worm::roll_back() {
    bool r = state_manager.try_activate(StateEnum::Rolling, *this);

    if (r)
        getLog().write("Gusano %hhu, jugador dando una vuelta\n", id);
}


ObjectType Worm::get_id() const { return WORM; }

uint16_t Worm::get_state() const { return state_manager.current; }

bool Worm::validate_client(uint16_t id_) const { return id_ == this->client_id; }

void Worm::fire() {
    state_manager.try_activate(StateEnum::Firing, *this);
    getLog().write("Gusano %hhu, jugador dispara\n", id);
}

void Worm::aim(float x, float y) {
    state_manager.try_activate(StateEnum::Aiming, *this);

    aim_x = x;
    aim_y = y;

    getLog().write("Gusano %hhu, jugador apunta hacia %f, %f\n", id, x, y);
}

void Worm::stop_aim() {
    state_manager.deactivate_states(StateEnum::Aiming, *this);
    getLog().write("Gusano %hhu, jugador deja de apuntar\n", id);
}

void Worm::power() {
    if (state_manager.try_activate(StateEnum::Powering, *this)) {
        state_manager.try_activate(StateEnum::Aiming, *this);
        getLog().write("Gusano %hhu, jugador potenciando su ataque\n", id);
    }
}

void Worm::stop_power() {
    state_manager.deactivate_states(StateEnum::Powering, *this);
    getLog().write("Gusano %hhu, jugador deja de cambiar la potencia de su ataque\n", id);
}
std::unique_ptr<GameObjectInfo> Worm::get_status() const {
    return std::make_unique<WormInfo>(*this);
}

std::unique_ptr<WormInfo> Worm::get_worminfo() const { return std::make_unique<WormInfo>(*this); }

void Worm::get_hit(float d) { health -= (uint8_t)fmin(d, health); }

void Worm::change_weapon(uint8_t weapon_id) {
    auto it = weapons_map.find(weapon_id);
    if (it != weapons_map.end())
        current_weapon = weapon_id;
}

std::unique_ptr<WeaponInfo> Worm::get_current_weapon_info() const {
    auto it = weapons_map.find(current_weapon);
    if (it != weapons_map.end())
        return it->second->get_info();
}

void Worm::set_active() { state_manager.try_activate(Active, *this); }

void Worm::set_deactive() {
    state_manager.deactivate_states(Active, *this);
    had_used_weapon = false;
}

void Worm::clear_attributes() {
    current_weapon = BAZOOKA_ID;
    jumpTimeout = 0;
    aim_x = 0;
    aim_y = 0;
    recent_health = health;
    recent_speed = 0;
    had_used_weapon = false;
}
