#include <vector>

#include "client_command.h"

class Move: public Command {
private:
    int dir;

public:
    enum Direction { Left = 1, Right = 2 };
    explicit Move(int dir);
    void serialize(uint16_t worm, ClientProtocol& protocol) override;
};
