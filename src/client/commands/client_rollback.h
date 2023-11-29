//
// Created by xguss on 10/11/23.
//

#ifndef WORMS_CLIENT_ROLLBACK_H
#define WORMS_CLIENT_ROLLBACK_H

#include <vector>

#include "client_command.h"


class Rollback: public Command {
private:
public:
    Rollback();
    void serialize(uint16_t worm, ClientProtocol& protocol) override;
};

#endif  // WORMS_CLIENT_ROLLBACK_H
