//
// Created by xguss on 10/09/23.
//

#include <stdexcept>
#include "server_protocol.h"
#include "utility"

struct InvalidMsg: public std::runtime_error {
    InvalidMsg(): std::runtime_error("The message is invalid") {}
};

ProtocolGameInterface::ProtocolGameInterface(Socket skt): BaseProtocol(std::move(skt)) {}

void ProtocolGameInterface::send_mov(uint8_t type) {

    send_1byte_number(1);
    send_1byte_number(type);
}

uint8_t ProtocolGameInterface::recv_msg() {
    u_int8_t status = 0;
    recv_1byte_number(status);

    if (status != 1)
        throw InvalidMsg();

    uint8_t type = 0;
    this->recv_1byte_number(type);

    return type;
}
