//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_CLIENT_EVENT_HANDLER_H
#define WORMS_CLIENT_EVENT_HANDLER_H

#include <memory>

#include "../common/common_liberror.h"
#include "commands/client_command.h"

#include "graphics/weapons/weapon_selector.h"

struct QuitGameClientInput: public LibError {
    QuitGameClientInput(): LibError(EBADRQC, "Exiting game") {}
};

class EventHandler {
private:
    std::shared_ptr<Command> move_left();
    std::shared_ptr<Command> move_right();
    std::shared_ptr<Command> stop_moving();
    std::shared_ptr<Command> jump();
    std::shared_ptr<Command> rollback();
    bool moving_right;
    bool moving_left;
    bool aiming;

public:
    EventHandler();
    std::shared_ptr<Command> handle(const SDL_Event& event, WeaponSelector& weapons_selector);
    std::shared_ptr<Command> aim(int x, int y);
    std::shared_ptr<Command> fire();
    std::shared_ptr<Command> stop_aim();

    std::shared_ptr<Command> power_attack();
};
#endif  // WORMS_CLIENT_EVENT_HANDLER_H
