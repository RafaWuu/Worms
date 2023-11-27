//
// Created by xguss on 03/11/23.
//

#ifndef WORMS_SERVER_INPUTS_H
#define WORMS_SERVER_INPUTS_H

#include "common_protocol_constants.h"

enum Input {
    StartGame = GAME_START_GAME,
    Move = GAME_MOVE,
    Jump = GAME_JUMP,
    Rollback = GAME_ROLLBACK,
    Fire = GAME_FIRE,
    Aim = GAME_AIM,
    Power = GAME_POWER,
    DirAttack = GAME_DATTACK,
    CountDown = GAME_COUNTDOWN,
    ChangeWeapon = GAME_GUNSELECT
};

enum MoveEnum { MoveLeft = 1, MoveRight = 2, StopMove = 3 };

enum MoveDir { DirLeft = 1, DirRight = 2 };

enum AimType {
    AimUp = 1,
    AimStop = 2,
};

enum PowerType { PowerUp = 1, PowerStop = 2 };

#endif  // WORMS_SERVER_INPUTS_H
