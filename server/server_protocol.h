//
// Created by xguss on 10/09/23.
//

#ifndef SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H
#define SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H

#include <string>

#include "../common/common_baseprotocol.h"
#include "../common/common_socket.h"

class ProtocolGameInterface : public BaseProtocol {
public:
    explicit ProtocolGameInterface(Socket skt);

    ProtocolGameInterface(const ProtocolGameInterface&) = delete;
    ProtocolGameInterface& operator=(const ProtocolGameInterface&) = delete;

    // Devuelven 1 si hubo un error en la comunicacion
    void send_mov(uint8_t type);
    uint8_t recv_msg();
};

#endif  // SOCKETS_2023C2_ABRAIDA_SERVER_PROTOCOL_GAMEINTERFACE_H
