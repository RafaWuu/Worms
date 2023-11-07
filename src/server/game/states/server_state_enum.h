//
// Created by xguss on 07/11/23.
//

#ifndef WORMS_SERVER_STATE_ENUM_H
#define WORMS_SERVER_STATE_ENUM_H

enum StateEnum {
    Alive = 0x001,
    Standing = 0x002,
    Walking = 0x004,
    Jumping = 0x008,

    Rolling = 0x010,
    Falling = 0x020,
    Firing = 0x040,
    ASD = 0x080,
    asd = 0x100

};

#endif  // WORMS_SERVER_STATE_ENUM_H