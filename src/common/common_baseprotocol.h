//
// Created by xguss on 24/09/23.
//

#ifndef SOCKETS_2023C2_ABRAIDA_COMMON_BASEPROTOCOL_H
#define SOCKETS_2023C2_ABRAIDA_COMMON_BASEPROTOCOL_H

#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>

#include "common_socket.h"

class BaseProtocol {
private:
    Socket skt;
    void recv_throw(void* v, size_t n);
    void send_throw(void* v, size_t n);

public:
    BaseProtocol(const std::string& hostname, const std::string& servname);
    explicit BaseProtocol(Socket socket);

    // devuelven si el socket fue cerrado
    void send_4byte_number(uint32_t number);
    void send_2byte_number(uint16_t number);
    void send_1byte_number(uint8_t number);
    void recv_4byte_number(uint32_t& number);
    void recv_2byte_number(uint16_t& number);
    void recv_1byte_number(uint8_t& number);
    void send_char_vector(std::vector<char>& buffer);
    void recv_char_vector(std::vector<char>& buffer);

    void kill();
};
#endif  // SOCKETS_2023C2_ABRAIDA_COMMON_BASEPROTOCOL_H
