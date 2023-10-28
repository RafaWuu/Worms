#include "client_protocol.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <arpa/inet.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE 1

#define BYTE 1

ClientProtocol::ClientProtocol(Socket&& socket): socket(std::move(socket)) {}


void ClientProtocol::close() {
    socket.shutdown(SHUT_RDWR);
    socket.close();
}

int ClientProtocol::send_msg(std::vector<uint8_t> serialized_action) {
    bool was_closed = false;

    socket.sendall(serialized_action.data(), serialized_action.size(), &was_closed);
    if (was_closed) {
        close();
        return FAILURE;
    }

    return SUCCESS;
}

