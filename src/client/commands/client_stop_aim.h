//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_CLIENT_STOP_AIM_H
#define WORMS_CLIENT_STOP_AIM_H

#include "client_command.h"
class StopAim: public Command {
public:
    void serialize(uint16_t worm, ClientProtocol& protocol) override;
};
#endif  // WORMS_CLIENT_STOP_AIM_H
