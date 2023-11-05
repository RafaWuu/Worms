//
// Created by xguss on 05/11/23.
//

#include "server_worm_sensor.h"

#include "b2_fixture.h"
#include "b2_polygon_shape.h"


WormSensor::WormSensor(Worm* worm): worm(worm), GameObject() {
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.45, 0.2, b2Vec2(0, -.2), 0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    fixtureDef.isSensor = true;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    worm->body->CreateFixture(&fixtureDef);
}


ObjectType WormSensor::get_id() { return WORM_SENSOR; }

void WormSensor::handle_begin_floor_contact(GameObject* other) {
    if (other->get_id() == BEAM)
        worm->numFootContacts++;
}

void WormSensor::handle_end_floor_contact(GameObject* other) {
    if (other->get_id() == BEAM)
        worm->numFootContacts--;
}
