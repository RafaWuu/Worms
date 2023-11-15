#include "client_command.h"
#include <vector>

class Move: public Command {
private:
    int dir;

public:
    enum Direction { Left = 1, Right = 2 };
    explicit Move(int dir);
    void serialize(ClientProtocol& protocol) override;
};
