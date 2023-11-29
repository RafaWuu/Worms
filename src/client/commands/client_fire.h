//
// Created by xguss on 14/11/23.
//

#ifndef WORMS_CLIENT_FIRE_H
#define WORMS_CLIENT_FIRE_H

#include "client_command.h"
class Fire: public Command {
public:
    void serialize(uint16_t worm, ClientProtocol& protocol) override;
};
#endif  // WORMS_CLIENT_FIRE_H
