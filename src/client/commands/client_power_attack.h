//
// Created by xguss on 17/11/23.
//

#ifndef WORMS_CLIENT_POWER_ATTACK_H
#define WORMS_CLIENT_POWER_ATTACK_H

#include "client_command.h"

class PowerAttack: public Command {

public:
    PowerAttack();
    void serialize(ClientProtocol& protocol) override;
};
#endif  // WORMS_CLIENT_POWER_ATTACK_H
