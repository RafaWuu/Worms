//
// Created by xguss on 07/11/23.
//

#ifndef WORMS_CLIENT_JUMP_H
#define WORMS_CLIENT_JUMP_H

#include "client_command.h"
#include <vector>

class Jump: public Command {
private:
    int type;

public:
    enum Type { Forward = 4, Backwards = 5 };
    explicit Jump(Type type);
    std::vector<uint8_t> serialize(ClientProtocol& protocol) override;
};


#endif //WORMS_CLIENT_JUMP_H
