//
// Created by xguss on 14/11/23.
//

#include "client_event_handler.h"

#include "commands/client_aim.h"
#include "commands/client_fire.h"
#include "commands/client_jump.h"
#include "commands/client_move.h"
#include "commands/client_rollback.h"
#include "commands/client_stop_aim.h"
#include "commands/client_stop_moving.h"
std::shared_ptr<Command> EventHandler::handle(SDL_Event& event) {
    if (event.type == SDL_QUIT) {
        throw (QuitGameClientInput());
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

    if (event.type == SDL_MOUSEBUTTONDOWN){
        if (event.button.button == SDL_BUTTON_LEFT)
            return aim(event.button.x, event.button.y);
        if (event.button.button == SDL_BUTTON_RIGHT)
            return fire();
    }

    if (event.type == SDL_MOUSEBUTTONUP){
        if (event.button.button == SDL_BUTTON_LEFT)
            return stop_aim();
    }

    if(aiming){
        int x;
        int y;
        SDL_GetMouseState(&x, &y);
        return aim(x, y);
    }


    return nullptr;
}

std::shared_ptr<Command> EventHandler::move_left() {
    if(!moving_right) {
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
    if(moving_right) {
        moving_right = false;
        return std::make_shared<StopMoving>();
    }

    if (moving_left) {
        moving_left = false;
        return std::make_shared<StopMoving>();
    }

    return nullptr;
}

std::shared_ptr<Command> EventHandler::jump(){
    return std::make_shared<Jump>();
}

std::shared_ptr<Command> EventHandler::rollback(){
    return std::make_shared<Rollback>();
}
std::shared_ptr<Command> EventHandler::aim(int x, int y) {
    aiming = true;
    return std::make_shared<Aim>(x, y);
}

std::shared_ptr<Command> EventHandler::fire() {
    return std::make_shared<Fire>();
}
std::shared_ptr<Command> EventHandler::stop_aim() {
    if (aiming) {
        aiming = false;
        return std::make_shared<StopAim>();
    }

    return nullptr;
}
EventHandler::EventHandler() {
    moving_left = false;
    moving_right = false;
    aiming = false;
}
