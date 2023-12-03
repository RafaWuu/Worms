//
// Created by xguss on 05/11/23.
//

#include "server_worm_sensor.h"

#include <memory>

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_worm_sensor_info.h"

WormSensor::WormSensor(Worm* worm): worm(worm), GameObject() {
    b2PolygonShape dynamicBox;
    auto& config = Configuration::get_instance();
    dynamicBox.SetAsBox(config.worm_width / 2 * 1.1, .15, b2Vec2(0, -config.worm_height / 2 + .1),
                        0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    fixtureDef.filter.categoryBits = WORM_SENSOR;
    fixtureDef.filter.maskBits = BOUNDARY | BEAM;

    fixtureDef.isSensor = true;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    worm->body->CreateFixture(&fixtureDef);
}


void WormSensor::handle_begin_floor_contact(GameObject* other) {
    if ((other->get_id() & (BEAM | GROUND)) != 0)
        worm->numFootContacts++;
}

void WormSensor::handle_end_floor_contact(GameObject* other) {
    if ((other->get_id() & (BEAM | GROUND)) != 0)
        worm->numFootContacts--;
}
ObjectType WormSensor::get_id() const { return WORM_SENSOR; }

std::unique_ptr<GameObjectInfo> WormSensor::get_status() const {
    return std::make_unique<WormSensorInfo>(*this);
}

void WormSensor::update(GameWorld& world) {
    if (worm == nullptr || worm->is_dead)
        is_dead = true;
}
