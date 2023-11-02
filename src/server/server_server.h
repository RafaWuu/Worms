//
// Created by xguss on 24/09/23.
//

#ifndef SOCKETS_2023C2_ABRAIDA_SERVER_SERVER_H
#define SOCKETS_2023C2_ABRAIDA_SERVER_SERVER_H

#include <string>

#include "server_accepter.h"
#include "server_protocol.h"

class Server {
private:
    Socket sk;

public:
    explicit Server(const std::string& port);
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    void run();
};

#endif  // SOCKETS_2023C2_ABRAIDA_SERVER_SERVER_H
