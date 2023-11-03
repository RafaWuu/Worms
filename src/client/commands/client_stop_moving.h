#include "client_command.h"
#include <vector>

class StopMoving : public Command {
public:
    StopMoving();
    std::vector<uint8_t> serialize(ClientProtocol& protocol) override;
};
