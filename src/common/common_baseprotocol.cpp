#include "common_baseprotocol.h"

#include <stdexcept>
#include <string>

#include <netinet/in.h>

#include "common_socket.h"
#include "utility"
//
// Created by xguss on 24/09/23.
//

BaseProtocol::BaseProtocol(const std::string& hostname, const std::string& servname):
        skt(hostname.c_str(), servname.c_str()) {}

BaseProtocol::BaseProtocol(Socket socket): skt(std::move(socket)) {}


void BaseProtocol::send_4byte_number(uint32_t number) {
    uint32_t num = htonl(number);
    send_throw(&num, sizeof(uint32_t));
}

void BaseProtocol::send_2byte_number(uint16_t number) {
    uint16_t num = htons(number);
    send_throw(&num, sizeof(uint16_t));
}


void BaseProtocol::send_1byte_number(uint8_t number) { send_throw(&number, sizeof(uint8_t)); }

void BaseProtocol::recv_4byte_number(uint32_t& number) {
    recv_throw(&number, sizeof(uint32_t));
    number = ntohl(number);
}

void BaseProtocol::send_4byte_float(float number) {

    uint32_t num = htonl((uint32_t)number);
    send_throw(&num, sizeof(uint32_t));
}

void BaseProtocol::recv_4byte_float(float& number) {
    uint32_t num;
    recv_throw(&num, sizeof(uint32_t));
    num = ntohl(num);


    number = (float)(*(char*)&num);
}

void BaseProtocol::recv_2byte_number(uint16_t& number) {
    recv_throw(&number, sizeof(uint16_t));
    number = ntohs(number);
}

void BaseProtocol::recv_1byte_number(uint8_t& number) { recv_throw(&number, sizeof(uint8_t)); }

void BaseProtocol::send_char_vector(std::vector<char>& buffer) {
    send_throw(buffer.data(), buffer.size());
}

void BaseProtocol::send_uint_vector(std::vector<uint8_t>& buffer) {
    send_throw(buffer.data(), buffer.size());
}

void BaseProtocol::recv_char_vector(std::vector<char>& buffer) {
    recv_throw(buffer.data(), buffer.size());
}

void BaseProtocol::kill() {
    skt.shutdown(SHUT_RDWR);
    skt.close();
}

void BaseProtocol::recv_throw(void* v, size_t n) {
    bool was_closed = false;

    skt.recvall(v, n, &was_closed);

    if (was_closed)
        throw ClosedSocket();
}

void BaseProtocol::send_throw(void* v, size_t n) {
    bool was_closed = false;

    skt.sendall(v, n, &was_closed);

    if (was_closed)
        throw ClosedSocket();
}
