#include "client_command.h"
#include <vector>

class StopMoving : public Command {
public:
    StopMoving();
    void serialize(ClientProtocol& protocol) override;
};
