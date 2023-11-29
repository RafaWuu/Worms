#include <vector>

#include "client_command.h"

class StopMoving: public Command {
public:
    StopMoving();
    void serialize(uint16_t worm, ClientProtocol& protocol) override;
};
