//
// Created by xguss on 07/11/23.
//

#include "server_states.h"

AliveState::AliveState() {
    code = Alive;
    required = 0;
    blocking_me = 0;
    terminate = 0;
    requiring = Standing | Walking | Jumping | Rolling | Falling | Firing | Aiming | Powering;
}

bool AliveState::update(Worm& worm) {
    if (worm.health > 0)
        return true;
    return false;
}

WalkingState::WalkingState() {
    code = Walking;
    required = Alive;
    blocking_me = Jumping | Rolling | Falling;
    terminate = Standing;
    requiring = NoState;
}

bool WalkingState::update(Worm& worm) {
    float desired_vel = .4;

    if (!worm.facing_right)
        desired_vel = -desired_vel;

    b2Vec2 vel = worm.body->GetLinearVelocity();

    float vel_change_x = desired_vel - vel.x;


    float impulse_x = worm.body->GetMass() * vel_change_x;

    worm.body->ApplyLinearImpulse(b2Vec2(impulse_x, 0), worm.body->GetWorldCenter(), true);
    return true;
}

StandingState::StandingState() {
    code = Standing;
    required = Alive;
    blocking_me = Jumping | Rolling | Falling;
    terminate = Walking;
    requiring = NoState;
}

bool StandingState::update(Worm& worm) {
    b2Vec2 vel = worm.body->GetLinearVelocity();
    float desired_vel = vel.x * 0.990f;

    float vel_change_x = desired_vel - vel.x;

    float impulse_x = worm.body->GetMass() * vel_change_x;

    worm.body->ApplyLinearImpulse(b2Vec2(impulse_x, 0), worm.body->GetWorldCenter(), true);
    return true;
}

JumpingState::JumpingState() {
    code = Jumping;
    required = Alive;
    blocking_me = Rolling | Falling;
    terminate = Walking | Standing | Aiming;
    requiring = NoState;

    remaining_frames = 0;
    last_moving_state = NoState;
}

void JumpingState::on_activated(Worm& worm) {
    remaining_frames = 8;
    worm.jumpTimeout = 10;


    last_moving_state = worm.get_state() & (Walking | Standing);
}

bool JumpingState::update(Worm& worm) {
    if (remaining_frames == 0)
        return false;

    float force_x = 15;
    float force_y = 20;


    if (!worm.facing_right)
        force_x = -force_x;

    worm.body->ApplyForce(b2Vec2(force_x, force_y), worm.body->GetWorldCenter(), true);

    remaining_frames--;
    return true;
}

bool JumpingState::can_be_activated(Worm& worm) {
    return worm.jumpTimeout == 0 && worm.numFootContacts > 0;
}

uint16_t JumpingState::on_deactivated(Worm& worm) { return NoState; }

RollingState::RollingState() {
    code = Rolling;
    required = Alive;
    blocking_me = Jumping | Falling;
    terminate = Walking | Standing | Aiming;
    requiring = NoState;

    remaining_frames = 0;
    last_moving_state = NoState;
}

void RollingState::on_activated(Worm& worm) {
    remaining_frames = 8;
    worm.jumpTimeout = 10;
    last_moving_state = worm.get_state() & (Walking | Standing);
}

bool RollingState::update(Worm& worm) {
    if (remaining_frames == 0)
        return false;

    float force_x = -6;
    float force_y = 25;
    if (!worm.facing_right)
        force_x = -force_x;

    worm.body->ApplyForce(b2Vec2(force_x, force_y), worm.body->GetWorldCenter(), true);

    remaining_frames--;
    return true;
}

bool RollingState::can_be_activated(Worm& worm) {
    return worm.jumpTimeout == 0 && worm.numFootContacts > 0;
}

uint16_t RollingState::on_deactivated(Worm& worm) { return NoState; }

FallingState::FallingState() {
    code = Falling;
    required = Alive;
    blocking_me = Jumping | Rolling;
    terminate = Aiming | Walking | Standing;
    requiring = NoState;

    max_y = 0;
}

void FallingState::on_activated(Worm& worm) { max_y = worm.body->GetPosition().y; }

bool FallingState::update(Worm& worm) {
    if (worm.body->GetPosition().y > max_y)
        max_y = worm.body->GetPosition().y;

    return worm.numFootContacts < 1;
}

uint16_t FallingState::on_deactivated(Worm& worm) {
    worm.process_fall(max_y - worm.body->GetPosition().y);
    worm.jumpTimeout = 3;
    return Standing;
}

FiringState::FiringState() {
    code = Firing;
    required = Powering;
    blocking_me = NoState;
    terminate = Aiming | Powering;
    requiring = NoState;
}


bool FiringState::update(Worm& worm) {
    b2Vec2 source = b2Vec2(1.5, .2);

    if (!worm.facing_right) {
        source.x = -source.x;
    }

    worm.current_gun.fire_proyectil(worm.body->GetWorldPoint(source), worm.desiredAngle);

    return false;
}

AimingState::AimingState() {
    code = Aiming;
    required = Alive;
    blocking_me = Jumping | Rolling | Falling;
    terminate = Walking;
    requiring = Powering;
}

bool AimingState::update(Worm& worm) {
    b2Vec2 toTarget = worm.body->GetLocalPoint(b2Vec2(worm.aim_x, worm.aim_y));

    if (worm.facing_right && toTarget.x < 0) {
        worm.desiredAngle = (toTarget.y > 0) ? M_PI_2f32 : -M_PI_2f32;
        return true;
    }

    if (!worm.facing_right && toTarget.x > 0) {
        worm.desiredAngle = (toTarget.y > 0) ? M_PI_2f32 : -M_PI_2f32;
        return true;
    }

    worm.desiredAngle = atan2f(toTarget.y, toTarget.x);

    return true;
}

PoweringState::PoweringState() {
    code = Powering;
    required = Aiming;
    blocking_me = NoState;
    terminate = NoState;
    requiring = Firing;
}

bool PoweringState::update(Worm& worm) {
    worm.aim_power += 0.01;

    if (worm.aim_power > 1) {
        worm.aim_power = 1;
        return false;
    }
    return true;
}

uint16_t PoweringState::on_deactivated(Worm& worm) {
    worm.aim_power = 0;
    return Firing;
}
