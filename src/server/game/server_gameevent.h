//
// Created by xguss on 02/11/23.
//

#ifndef WORMS_SERVER_GAMEEVENT_H
#define WORMS_SERVER_GAMEEVENT_H

#include <cstdint>

#include "server_event_handler.h"
#include "server_move.h"


class GameEvent {
protected:
    uint16_t client_id;

public:
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
    GameEventMove(uint16_t client_id, uint8_t worm_id, InputEnum code);
    void execute(EventHandler& e) override;

private:
    InputEnum code;
    uint8_t worm_id;
};

#endif  // WORMS_SERVER_GAMEEVENT_H
