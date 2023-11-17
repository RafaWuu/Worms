//
// Created by xguss on 15/11/23.
//

#ifndef WORMS_COMMON_BASEPROTOCOL_MOCK_H
#define WORMS_COMMON_BASEPROTOCOL_MOCK_H

#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "common_baseprotocol.h"

class MockBaseProtocol: public BaseProtocol {
public:
    MOCK_METHOD(void, send_1byte_number, (uint8_t number), (override));
    MOCK_METHOD(void, send_2byte_number, (uint16_t number), (override));
    MOCK_METHOD(void, send_4byte_number, (uint32_t number), (override));
    MOCK_METHOD(void, send_4byte_float, (float number), (override));
    MOCK_METHOD(void, send_uint_vector, (std::vector<uint8_t> & buffer), (override));
    MOCK_METHOD(void, send_char_vector, (std::vector<char> & buffer), (override));

    MOCK_METHOD(void, recv_1byte_number, (uint8_t & number), (override));
    MOCK_METHOD(void, recv_2byte_number, (uint16_t & number), (override));
    MOCK_METHOD(void, recv_4byte_number, (uint32_t & number), (override));
    MOCK_METHOD(void, recv_4byte_float, (float& number), (override));
    MOCK_METHOD(void, recv_char_vector, (std::vector<char> & buffer), (override));

    MOCK_METHOD(void, kill, (), (override));
};

#endif  // WORMS_COMMON_BASEPROTOCOL_MOCK_H
