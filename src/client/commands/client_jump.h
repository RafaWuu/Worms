//
// Created by xguss on 07/11/23.
//

#ifndef WORMS_CLIENT_JUMP_H
#define WORMS_CLIENT_JUMP_H

#include <vector>

#include "client_command.h"

class Jump: public Command {
private:
public:
    Jump();
    void serialize(uint16_t worm, ClientProtocol& protocol) override;
};


#endif  // WORMS_CLIENT_JUMP_H
