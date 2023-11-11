//
// Created by xguss on 07/11/23.
//

#ifndef WORMS_SERVER_STATE_H
#define WORMS_SERVER_STATE_H

#include <cstdint>

#include "game/entities/server_worm.h"
#include "game/server_inputs.h"

class Worm;

class WormState {
private:
    bool _is_active;

protected:
    uint16_t code;
    uint16_t required;
    uint16_t blocking_me;
    uint16_t terminate;
    uint16_t requiring;

public:
    WormState() = default;
    virtual bool can_be_activated(Worm& worm);
    virtual bool update(Worm& worm) = 0;


    uint16_t get_states_blocking_me() const;  // Me bloquean

    uint16_t get_states_required() const;  // Los necesito

    uint16_t get_states_to_terminate() const;  // Yo bloqueo

    uint16_t get_states_requiring();  // Me necesitan

    uint16_t get_code() const;

    virtual void on_activated(Worm& worm);
    virtual uint16_t on_deactivated(Worm& worm); // Devuelve estados que deben activarse

};
#endif  // WORMS_SERVER_STATE_H
