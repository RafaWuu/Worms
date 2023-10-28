#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>

#include <string.h>

#include "../common/common_socket.h"


class ClientProtocol {
private:
    Socket socket;

public:
    explicit ClientProtocol(Socket&& socket);

    /* Recibe el comando serializado y lo manda al servidor */
    int send_msg(std::vector<uint8_t> serialized_action);

    /* Shutdown y close del socket */
    void close();
};

#endif
