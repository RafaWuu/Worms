//
// Created by xguss on 07/11/23.
//

#ifndef WORMS_SERVER_STATE_WALKING_H
#define WORMS_SERVER_STATE_WALKING_H

#include "game/entities/server_worm.h"

#include "server_state.h"


class AliveState: public WormState {
public:
    AliveState();
    void update(Worm& worm) override;
};

class StandingState: public WormState {
public:
    StandingState();
    void update(Worm& worm) override;
};

class WalkingState: public WormState {
public:
    WalkingState();
    void update(Worm& worm) override;
};

class JumpingState: public WormState {
private:
    uint8_t remaining_frames;

public:
    JumpingState();
    void update(Worm& worm) override;
    void on_activated(Worm& worm) override;
    bool can_be_activated(Worm& worm) override;
};

class RollingState: public WormState {
private:
    uint8_t remaining_frames;

public:
    RollingState();
    void update(Worm& worm) override;
    void on_activated(Worm& worm) override;
    bool can_be_activated(Worm& worm) override;
};


#endif  // WORMS_SERVER_STATE_WALKING_H
