#ifndef COMMON_COMMAND_H
#define COMMON_COMMAND_H

#include <string>
#include <vector>

#include "../client_protocol.h"

class Command {
public:
    Command();
    virtual void serialize(ClientProtocol& protocol) = 0;
};

#endif
