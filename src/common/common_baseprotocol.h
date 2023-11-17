//
// Created by xguss on 15/11/23.
//

#ifndef WORMS_COMMON_BASEPROTOCOL_H
#define WORMS_COMMON_BASEPROTOCOL_H

#include <cstdint>
#include <stdexcept>
#include <vector>

class BaseProtocol {
public:
    BaseProtocol() = default;
    virtual ~BaseProtocol() = default;
    virtual void send_1byte_number(uint8_t number) = 0;
    virtual void send_2byte_number(uint16_t number) = 0;
    virtual void send_4byte_number(uint32_t number) = 0;
    virtual void send_4byte_float(float number) = 0;
    virtual void send_uint_vector(std::vector<uint8_t>& buffer) = 0;
    virtual void send_char_vector(std::vector<char>& buffer) = 0;

    virtual void recv_1byte_number(uint8_t& number) = 0;
    virtual void recv_2byte_number(uint16_t& number) = 0;
    virtual void recv_4byte_number(uint32_t& number) = 0;
    virtual void recv_4byte_float(float& number) = 0;
    virtual void recv_char_vector(std::vector<char>& buffer) = 0;

    virtual void kill() = 0;
};
#endif  // WORMS_COMMON_BASEPROTOCOL_H
