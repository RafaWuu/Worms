//
// Created by xguss on 14/11/23.
//

#include "client_event_handler.h"

#include <memory>

#include "commands/change_weapon.h"
#include "commands/client_aim.h"
#include "commands/client_fire.h"
#include "commands/client_jump.h"
#include "commands/client_move.h"
#include "commands/client_power_attack.h"
#include "commands/client_rollback.h"
#include "commands/client_stop_aim.h"
#include "commands/client_stop_moving.h"
#include "graphics/weapons/weapon_selector.h"

EventHandler::EventHandler() {
    moving_left = false;
    moving_right = false;
    aiming = false;
}

std::shared_ptr<Command> EventHandler::handle(const SDL_Event& event,
                                              WeaponSelector& weapon_selector) {
    if (event.type == SDL_QUIT) {
        throw(QuitGameClientInput());
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
            case SDLK_q:
                throw(QuitGameClientInput());
            case SDLK_a:
                return jump();
            case SDLK_s:
                return rollback();
            case SDLK_LEFT:
                return move_left();
            case SDLK_RIGHT:
                return move_right();
        }
    }

    if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                return stop_moving();
            case SDLK_RIGHT:
                return stop_moving();
        }
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            if (weapon_selector.mouse_inside(event.button.x, event.button.y)) {
                uint8_t weapon_id = weapon_selector.get_weapon_index(event.button.x, event.button.y);
                return change_weapon(weapon_id);
            }
            if (!aiming)
                return aim(event.button.x, event.button.y);
        }
        if (event.button.button == SDL_BUTTON_RIGHT && aiming)
            return power_attack();
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT && aiming)
            return stop_aim();
        if (event.button.button == SDL_BUTTON_RIGHT && aiming)
            return fire();
    }

    if (aiming) {
        int x;
        int y;
        SDL_GetMouseState(&x, &y);
        return aim(x, y);
    }


    return nullptr;
}

std::shared_ptr<Command> EventHandler::change_weapon(int weapon_id) {
    return std::make_shared<ChangeWeapon>(weapon_id);
}

std::shared_ptr<Command> EventHandler::move_left() {
    if (!moving_right) {
        moving_right = true;
        return std::make_shared<Move>(Move::Direction::Left);
    }
    return nullptr;
}

std::shared_ptr<Command> EventHandler::move_right() {
    if (!moving_left) {
        moving_left = true;
        return std::make_shared<Move>(Move::Direction::Right);
    }

    return nullptr;
}

std::shared_ptr<Command> EventHandler::stop_moving() {
    if (moving_right) {
        moving_right = false;
        return std::make_shared<StopMoving>();
    }

    if (moving_left) {
        moving_left = false;
        return std::make_shared<StopMoving>();
    }

    return nullptr;
}

std::shared_ptr<Command> EventHandler::jump() { return std::make_shared<Jump>(); }

std::shared_ptr<Command> EventHandler::rollback() { return std::make_shared<Rollback>(); }
std::shared_ptr<Command> EventHandler::aim(int x, int y) {
    aiming = true;
    return std::make_shared<Aim>(x, y);
}

std::shared_ptr<Command> EventHandler::fire() {
    return aiming ? std::make_shared<Fire>() : nullptr;
}

std::shared_ptr<Command> EventHandler::stop_aim() {
    if (aiming) {
        aiming = false;
        return std::make_shared<StopAim>();
    }

    return nullptr;
}

std::shared_ptr<Command> EventHandler::power_attack() {
    return aiming ? std::make_shared<PowerAttack>() : nullptr;
}
