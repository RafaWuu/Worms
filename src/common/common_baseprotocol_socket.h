//
// Created by xguss on 24/09/23.
//

#ifndef SOCKETS_2023C2_ABRAIDA_COMMON_BASEPROTOCOL_H
#define SOCKETS_2023C2_ABRAIDA_COMMON_BASEPROTOCOL_H

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include "common_baseprotocol.h"
#include "common_socket.h"

class SocketBaseProtocol: public BaseProtocol {
private:
    Socket skt;
    void recv_throw(void* v, size_t n);
    void send_throw(void* v, size_t n);

public:
    explicit SocketBaseProtocol(Socket socket);
    ~SocketBaseProtocol() override = default;
    // devuelven si el socket fue cerrado
    void send_4byte_number(uint32_t number) override;
    void send_2byte_number(uint16_t number) override;
    void send_1byte_number(uint8_t number) override;
    void recv_4byte_number(uint32_t& number) override;
    void recv_2byte_number(uint16_t& number) override;
    void recv_1byte_number(uint8_t& number) override;
    void send_char_vector(std::vector<char>& buffer) override;
    void recv_char_vector(std::vector<char>& buffer) override;
    void send_uint_vector(std::vector<uint8_t>& buffer) override;

    void kill() override;

    void send_4byte_float(float number) override;

    void recv_4byte_float(float& number) override;
};
#endif  // SOCKETS_2023C2_ABRAIDA_COMMON_BASEPROTOCOL_H
