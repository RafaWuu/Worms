#include "client_command.h"

class Move : public Command {
private:
    int dir;

public:
    enum Direction {
        Left = 1,
        Right = 2
    };
    Move(int dir);
    std::vector<uint8_t> serialize(ClientProtocol& protocol) override;
};