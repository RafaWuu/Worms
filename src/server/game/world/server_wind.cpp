//
// Created by xguss on 03/12/23.
//

#include "server_wind.h"

#include "../../../../configuration/configuration.h"

#define WIND_MODIFIER 0.025

Wind::Wind():
        rd(),
        gen(rd()),
        dis(Configuration::get_instance().minimum_wind, Configuration::get_instance().maximum_wind),
        dis_bool(0, 1) {
    wind = dis(gen);

    if (dis_bool(gen) == 1)
        wind = -wind;
}

void Wind::update_wind() {
    wind = dis(gen);

    if (dis_bool(gen) == 1)
        wind = -wind;
}

void Wind::affect_projectile(b2Body& body) {
    float vel_x = wind > 0 ? fmax(wind - body.GetLinearVelocity().x, 0.f) :
                             fmin(wind - body.GetLinearVelocity().x, 0.f);


    float impulse_x = body.GetMass() * vel_x * WIND_MODIFIER;
    body.ApplyLinearImpulse(b2Vec2(impulse_x, 0), body.GetWorldCenter(), true);
}
