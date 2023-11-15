//
// Created by xguss on 10/11/23.
//

#ifndef WORMS_CLIENT_ROLLBACK_H
#define WORMS_CLIENT_ROLLBACK_H

#include "client_command.h"
#include <vector>


class Rollback: public Command {
private:

public:
    Rollback();
    void serialize(ClientProtocol& protocol) override;
};

#endif //WORMS_CLIENT_ROLLBACK_H
