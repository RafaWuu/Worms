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
    dynamicBox.SetAsBox(0.45, 0.35, b2Vec2(0, -.25), 0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

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
