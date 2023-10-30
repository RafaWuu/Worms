#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>

#include <string.h>

#include "../common/common_socket.h"
#include "../common/common_baseprotocol.h"


class ClientProtocol : public BaseProtocol {

public:
    explicit ClientProtocol(Socket socket);

    void send_move(uint8_t dir);

    /* Shutdown y close del socket */
    void close();
};

#endif
