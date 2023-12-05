

#include "server_worm_sensor.h"

#include <memory>

#include "b2_fixture.h"
#include "b2_polygon_shape.h"
#include "server_beam.h"
#include "server_worm_sensor_info.h"

WormSensor::WormSensor(Worm* worm): worm(worm), GameObject() {
    b2PolygonShape dynamicBox;
    const auto& config = Configuration::get_instance();
    dynamicBox.SetAsBox(config.worm_width / 2 * 1.1, .0005, b2Vec2(0, -config.worm_height / 2), 0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    fixtureDef.filter.categoryBits = WORM_SENSOR;
    fixtureDef.filter.maskBits = BOUNDARY | BEAM | GROUND | projectile;

    fixtureDef.isSensor = true;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    worm->body->CreateFixture(&fixtureDef);
}


void WormSensor::handle_begin_floor_contact(GameObject* other) {
    if ((other->get_id() & BEAM) == BEAM) {
        auto worm_fixture = this->worm->body->GetFixtureList();

        while (worm_fixture->IsSensor()) worm_fixture = worm_fixture->GetNext();

        auto other_beam = dynamic_cast<Beam*>(other);
        if (other_beam->is_walkable()) {
            worm->numFootContacts++;
            worm_fixture->SetFriction(.4);
            worm_fixture->SetRestitution(0);
            worm->body->SetGravityScale(0);
        }
    }

    if ((other->get_id() & GROUND) == GROUND) {
        worm->numFootContacts++;
        worm->process_water_fall();
    }
}

void WormSensor::handle_end_floor_contact(GameObject* other) {
    if ((other->get_id() & BEAM) == BEAM) {
        auto worm_fixture = this->worm->body->GetFixtureList();

        while (worm_fixture->IsSensor()) worm_fixture = worm_fixture->GetNext();
        auto other_beam = dynamic_cast<Beam*>(other);
        if (other_beam->is_walkable()) {
            worm->numFootContacts--;
            worm_fixture->SetFriction(Configuration::get_instance().worm_friction);
            worm_fixture->SetRestitution(Configuration::get_instance().worm_restitution);
            worm->body->SetGravityScale(1);
        }
    }
}
ObjectType WormSensor::get_id() const { return WORM_SENSOR; }

std::unique_ptr<GameObjectInfo> WormSensor::get_status() const {
    return std::make_unique<WormSensorInfo>(*this);
}

void WormSensor::update(GameWorld& world) {
    if (worm == nullptr || worm->is_dead)
        is_dead = true;
}
