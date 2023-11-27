#include "common_baseprotocol_socket.h"

#include <stdexcept>
#include <string>

#include <netinet/in.h>

#include "common_socket.h"
#include "utility"
//
// Created by xguss on 24/09/23.
//

#define FIXED_SCALE 10000.0f

SocketBaseProtocol::SocketBaseProtocol(Socket socket): skt(std::move(socket)) {}


void SocketBaseProtocol::send_4byte_number(uint32_t number) {
    uint32_t num = htonl(number);
    send_throw(&num, sizeof(uint32_t));
}

void SocketBaseProtocol::send_2byte_number(uint16_t number) {
    uint16_t num = htons(number);
    send_throw(&num, sizeof(uint16_t));
}


void SocketBaseProtocol::send_1byte_number(uint8_t number) { send_throw(&number, sizeof(uint8_t)); }

void SocketBaseProtocol::recv_4byte_number(uint32_t& number) {
    recv_throw(&number, sizeof(uint32_t));
    number = ntohl(number);
}

void SocketBaseProtocol::send_4byte_float(float number) {
    uint32_t n = std::abs(number * FIXED_SCALE);
    uint8_t b = number > 0;

    n = htonl(n);

    send_throw(&b, sizeof(uint8_t));
    send_throw(&n, sizeof(uint32_t));
}

void SocketBaseProtocol::recv_4byte_float(float& number) {
    uint8_t b;
    uint32_t n;

    recv_throw(&b, sizeof(uint8_t));
    recv_throw(&n, sizeof(uint32_t));

    number = ntohl(n) / FIXED_SCALE;

    if (!b)
        number = -number;
}

void SocketBaseProtocol::recv_2byte_number(uint16_t& number) {
    recv_throw(&number, sizeof(uint16_t));
    number = ntohs(number);
}

void SocketBaseProtocol::recv_1byte_number(uint8_t& number) {
    recv_throw(&number, sizeof(uint8_t));
}

void SocketBaseProtocol::send_char_vector(std::vector<char>& buffer) {
    send_throw(buffer.data(), buffer.size());
}

void SocketBaseProtocol::send_uint_vector(std::vector<uint8_t>& buffer) {
    send_throw(buffer.data(), buffer.size());
}

void SocketBaseProtocol::recv_char_vector(std::vector<char>& buffer) {
    recv_throw(buffer.data(), buffer.size());
}

void SocketBaseProtocol::kill() {
    skt.shutdown(SHUT_RDWR);
    skt.close();
}

void SocketBaseProtocol::recv_throw(void* v, size_t n) {
    bool was_closed = false;

    skt.recvall(v, n, &was_closed);

    if (was_closed)
        throw ClosedSocket();
}

void SocketBaseProtocol::send_throw(const void* v, size_t n) {
    bool was_closed = false;

    skt.sendall(v, n, &was_closed);

    if (was_closed)
        throw ClosedSocket();
}
