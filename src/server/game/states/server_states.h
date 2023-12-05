

#ifndef WORMS_SERVER_STATES_H
#define WORMS_SERVER_STATES_H

#include "game/entities/server_worm.h"

#include "server_state.h"


class AliveState: public WormState {
public:
    AliveState();
    bool update(Worm& worm) override;
    uint16_t on_deactivated(Worm& worm) override;
};

class StandingState: public WormState {
public:
    StandingState();
    bool update(Worm& worm) override;
};

class WalkingState: public WormState {
public:
    WalkingState();
    bool update(Worm& worm) override;
};

class JumpingState: public WormState {
private:
    uint8_t remaining_frames;

public:
    JumpingState();
    bool update(Worm& worm) override;
    void on_activated(Worm& worm) override;
    bool can_be_activated(Worm& worm) override;
    uint16_t on_deactivated(Worm& worm) override;
};

class RollingState: public WormState {
private:
    uint8_t remaining_frames;

public:
    RollingState();
    bool update(Worm& worm) override;
    void on_activated(Worm& worm) override;
    bool can_be_activated(Worm& worm) override;
    uint16_t on_deactivated(Worm& worm) override;
};

class FallingState: public WormState {
private:
    float max_y;

public:
    FallingState();
    bool update(Worm& worm) override;
    void on_activated(Worm& worm) override;
    uint16_t on_deactivated(Worm& worm) override;
};

class FiringState: public WormState {
public:
    FiringState();
    bool update(Worm& worm) override;
};

class AimingState: public WormState {
public:
    AimingState();
    bool can_be_activated(Worm& worm) override;
    bool update(Worm& worm) override;
};

class PoweringState: public WormState {
public:
    PoweringState();
    bool can_be_activated(Worm& worm) override;
    bool update(Worm& worm) override;
    uint16_t on_deactivated(Worm& worm) override;
};

class ActiveState: public WormState {
public:
    ActiveState();
    bool update(Worm& worm) override;
    uint16_t on_deactivated(Worm& worm) override;

    void on_activated(Worm& worm) override;
};

#endif  // WORMS_SERVER_STATES_H
