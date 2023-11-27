//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_GAMEEVENT_H
#define WORMS_SERVER_GAMEEVENT_H

#include <cstdint>

#include "server_event_handler.h"
#include "server_inputs.h"


class GameEvent {
protected:
    uint16_t client_id;

public:
    virtual ~GameEvent() = default;
    explicit GameEvent(uint16_t client_id): client_id(client_id) {}
    virtual void execute(EventHandler& e) = 0;
};


class GameEventStartGame: public GameEvent {
public:
    explicit GameEventStartGame(uint16_t client_id);
    void execute(EventHandler& e) override;
};


class GameEventMove: public GameEvent {
public:
    GameEventMove(uint16_t client_id, uint8_t worm_id, MoveDir dir);
    void execute(EventHandler& e) override;

private:
    MoveDir dir;
    uint8_t worm_id;
};


class GameEventStop: public GameEvent {
public:
    GameEventStop(uint16_t client_id, uint8_t worm_id);
    void execute(EventHandler& e) override;

private:
    uint8_t worm_id;
};


class GameEventJump: public GameEvent {
public:
    GameEventJump(uint16_t client_id, uint8_t worm_id);
    void execute(EventHandler& e) override;

private:
    uint8_t worm_id;
};


class GameEventRollBack: public GameEvent {
public:
    GameEventRollBack(uint16_t client_id, uint8_t worm_id);
    void execute(EventHandler& e) override;

private:
    uint8_t worm_id;
};


class GameEventFireGun: public GameEvent {
public:
    GameEventFireGun(uint16_t client_id, uint8_t worm_id);
    void execute(EventHandler& e) override;

private:
    uint8_t worm_id;
};


class GameEventAim: public GameEvent {
public:
    GameEventAim(uint16_t client_id, uint8_t worm_id, float x, float y);
    void execute(EventHandler& e) override;

private:
    uint8_t worm_id;
    float x, y;
};


class GameEventAimStop: public GameEvent {
public:
    GameEventAimStop(uint16_t client_id, uint8_t worm_id);
    void execute(EventHandler& e) override;

private:
    uint8_t worm_id;
};

class GameEventPower: public GameEvent {
public:
    GameEventPower(uint16_t client_id, uint8_t worm_id);
    void execute(EventHandler& e) override;

private:
    uint8_t worm_id;
};


class GameEventPowerStop: public GameEvent {

public:
    GameEventPowerStop(uint16_t client_id, uint8_t worm_id);
    void execute(EventHandler& e) override;

private:
    uint8_t worm_id;
};

class GameEventChangeWeapon: public GameEvent {

public:
    GameEventChangeWeapon(uint16_t client_id, uint8_t worm_id, uint8_t weapon_id);
    void execute(EventHandler& e) override;

private:
    uint8_t worm_id;
    uint8_t weapon_id;
};

#endif  // WORMS_SERVER_GAMEEVENT_H
