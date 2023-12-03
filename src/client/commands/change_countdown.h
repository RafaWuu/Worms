#include <vector>

#include "client_command.h"

class ChangeCountdown: public Command {
private:
    int countdown;

public:
    explicit ChangeCountdown(int countdown);
    void serialize(uint16_t worm, ClientProtocol& protocol) override;
};
