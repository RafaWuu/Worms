#ifndef COMMON_COMMAND_H
#define COMMON_COMMAND_H

#include <vector>
#include <string>
#include "../client_protocol.h"

class Command {
public:
    Command();
    virtual std::vector<uint8_t> serialize(ClientProtocol& protocol) = 0;
};

#endif