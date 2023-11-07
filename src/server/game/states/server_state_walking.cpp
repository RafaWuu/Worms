//
// Created by xguss on 07/11/23.
//

#include "server_state_walking.h"

AliveState::AliveState() {
    code = Alive;
    required = 0;
    blocking_me = 0;
    terminate = 0;
    requiring = Standing | Walking | Jumping | Rolling;
}

void AliveState::update(Worm& worm) {}

WalkingState::WalkingState() {
    code = Walking;
    required = Alive;
    blocking_me = Jumping | Rolling;
    terminate = Standing;
    requiring = 0;
}

void WalkingState::update(Worm& worm) {
    float desired_vel = .4;

    if (!worm.facing_right)
        desired_vel = -desired_vel;

    b2Vec2 vel = worm.body->GetLinearVelocity();

    float vel_change_x = desired_vel - vel.x;


    float impulse_x = worm.body->GetMass() * vel_change_x;

    worm.body->ApplyLinearImpulse(b2Vec2(impulse_x, 0), worm.body->GetWorldCenter(), true);
}

StandingState::StandingState() {
    code = Standing;
    required = Alive;
    blocking_me = Jumping | Rolling;
    terminate = Walking;
    requiring = 0;
}

void StandingState::update(Worm& worm) {
    b2Vec2 vel = worm.body->GetLinearVelocity();
    float desired_vel = vel.x * 0.990f;

    float vel_change_x = desired_vel - vel.x;

    float impulse_x = worm.body->GetMass() * vel_change_x;

    worm.body->ApplyLinearImpulse(b2Vec2(impulse_x, 0), worm.body->GetWorldCenter(), true);
}

JumpingState::JumpingState() {
    code = Jumping;
    required = Alive;
    blocking_me = Rolling;
    terminate = Walking | Standing;
    requiring = 0;

    remaining_frames = 0;
}

void JumpingState::update(Worm& worm) {
    if (remaining_frames == 0)
        return;

    float force_x = 15;

    if (!worm.facing_right)
        force_x = -force_x;

    worm.body->ApplyForce(b2Vec2(force_x, 25), worm.body->GetWorldCenter(), true);
    remaining_frames--;
}

void JumpingState::on_activated(Worm& worm) {
    remaining_frames = 8;
    worm.jumpTimeout = 12;
}

bool JumpingState::can_be_activated(Worm& worm) {
    return worm.jumpTimeout == 0 && worm.numFootContacts > 0;
}

RollingState::RollingState() {
    code = Rolling;
    required = Alive;
    blocking_me = Jumping;
    terminate = Walking | Standing;
    requiring = 0;

    remaining_frames = 0;
}

void RollingState::update(Worm& worm) {
    if (remaining_frames == 0)
        return;

    float force_x = -25;

    if (!worm.facing_right)
        force_x = -force_x;

    worm.body->ApplyForce(b2Vec2(force_x, 15), worm.body->GetWorldCenter(), true);
    remaining_frames--;
}

void RollingState::on_activated(Worm& worm) {
    remaining_frames = 8;
    worm.jumpTimeout = 12;
}

bool RollingState::can_be_activated(Worm& worm) {
    return worm.jumpTimeout == 0 && worm.numFootContacts > 0;
}
