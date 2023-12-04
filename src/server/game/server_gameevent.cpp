//
// Created by xguss on 02/11/23.
//

#include "server_gameevent.h"

void GameEventStartGame::execute(EventHandler& e) { e.create_game(this->client_id); }

GameEventStartGame::GameEventStartGame(uint16_t client_id): GameEvent(client_id) {}

GameEventMove::GameEventMove(uint16_t client_id, uint8_t worm_id, MoveDir dir):
        worm_id(worm_id), dir(dir), GameEvent(client_id) {}

void GameEventMove::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.move(dir);
}

GameEventStop::GameEventStop(uint16_t client_id, uint8_t worm_id):
        worm_id(worm_id), GameEvent(client_id) {}

void GameEventStop::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.stop_move();
}

GameEventJump::GameEventJump(uint16_t client_id, uint8_t worm_id):
        worm_id(worm_id), GameEvent(client_id) {}

void GameEventJump::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.jump();
}

GameEventRollBack::GameEventRollBack(uint16_t client_id, uint8_t worm_id):
        worm_id(worm_id), GameEvent(client_id) {}

void GameEventRollBack::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.roll_back();
}

GameEventFireGun::GameEventFireGun(uint16_t client_id, uint8_t worm_id):
        worm_id(worm_id), GameEvent(client_id) {}

void GameEventFireGun::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.fire();
}

GameEventAim::GameEventAim(uint16_t client_id, uint8_t worm_id, float x, float y):
        worm_id(worm_id), GameEvent(client_id) {

    this->x = x;
    this->y = y;
}

void GameEventAim::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.aim(x, y);
}

GameEventAimStop::GameEventAimStop(uint16_t client_id, uint8_t worm_id):
        worm_id(worm_id), GameEvent(client_id) {}

void GameEventAimStop::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.stop_aim();
}

GameEventPower::GameEventPower(uint16_t client_id, uint8_t worm_id):
        worm_id(worm_id), GameEvent(client_id) {}

void GameEventPower::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.power();
}

GameEventPowerStop::GameEventPowerStop(uint16_t client_id, uint8_t worm_id):
        worm_id(worm_id), GameEvent(client_id) {}

void GameEventPowerStop::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.stop_power();
}


GameEventChangeWeapon::GameEventChangeWeapon(uint16_t client_id, uint8_t worm_id,
                                             uint8_t weapon_id):
        worm_id(worm_id), weapon_id(weapon_id), GameEvent(client_id) {}

void GameEventChangeWeapon::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.change_weapon(weapon_id);
}

GameEventCountdown::GameEventCountdown(uint16_t client_id, uint8_t worm_id, uint8_t seconds):
        worm_id(worm_id), seconds(seconds), GameEvent(client_id) {}

void GameEventCountdown::execute(EventHandler& e) {
    Worm& worm = e.get_worm(this->worm_id, this->client_id);
    worm.set_countdown(seconds);
}
