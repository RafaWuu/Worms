//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_CLIENT_AIM_H
#define WORMS_CLIENT_AIM_H

#include "client_command.h"
class Aim : public Command{
private:
    float x;
    float y;
public:
    Aim(int x, int y);
    void serialize(ClientProtocol& protocol) override;
};

#endif  // WORMS_CLIENT_AIM_H
