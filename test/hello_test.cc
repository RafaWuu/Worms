//
// Created by xguss on 15/11/23.
//

#include <gtest/gtest.h>
#include <gmock/gmock-cardinalities.h>
#include "../src/common/common_baseprotocol_mock.h"
#include "../src/server/server_protocol.h"
#include "../src/server/lobby/server_lobby_request.h"
#include "../src/server/server_error.h"


using ::testing::AtLeast;
using ::testing::SetArgReferee;

TEST(ServerLobbyTest, LobbyThrowOnInvalidMsgRecv) {
    MockBaseProtocol protocol;
    MockBaseProtocol protocol2;

    // Codigo de lobby request invalido

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(LOBBY_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(99));

    EXPECT_CALL(protocol, recv_2byte_number)
            .Times(0);

    EXPECT_CALL(protocol, recv_char_vector)
            .Times(0);

    // Codigo de request al server invalido

    EXPECT_CALL(protocol2, recv_1byte_number)
            .Times(1)
            .WillOnce(SetArgReferee<0, uint8_t>(99));

    EXPECT_CALL(protocol2, recv_2byte_number)
            .Times(0);

    EXPECT_CALL(protocol2, recv_char_vector)
            .Times(0);

    ServerProtocol serverProtocol1(protocol);
    ServerProtocol serverProtocol2(protocol2);

    EXPECT_THROW(serverProtocol1.recv_lobby_msg(), InvalidMsg);
    EXPECT_THROW(serverProtocol2.recv_lobby_msg(), InvalidMsg);
}

TEST(ServerLobbyTest, LobbyThrowOnInvalidRecvCreateGameRequest) {
    MockBaseProtocol protocol;
    MockBaseProtocol protocol2;
    MockBaseProtocol protocol3;

    // Longitud de escenario invalida

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(LOBBY_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(CREATE_GAME));

    EXPECT_CALL(protocol, recv_2byte_number)
            .WillOnce(SetArgReferee<0, uint16_t>(0));

    EXPECT_CALL(protocol, recv_char_vector)
            .Times(0);

    ServerProtocol serverProtocol1(protocol);


    EXPECT_THROW(serverProtocol1.recv_lobby_msg(), InvalidMsg);
}

TEST(ServerLobbyTest, LobbyCanRecvCreateGameRequest) {
    MockBaseProtocol protocol;

    std::string s("asdfgh");

    std::vector scenario(s.begin(), s.end());

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(LOBBY_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(CREATE_GAME));

    EXPECT_CALL(protocol, recv_2byte_number)
            .WillOnce(SetArgReferee<0, uint16_t>(s.length()));

    EXPECT_CALL(protocol, recv_char_vector)
            .WillOnce(SetArgReferee<0>(scenario));

    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<LobbyRequest> req = serverProtocol.recv_lobby_msg();

    LobbyRequestNewGame* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<LobbyRequestNewGame*>(req.get()))
        << "No se creo la peticion del tipo adecuado";

    EXPECT_EQ(s, req2->scenario) << "Nombre de escenario incorrecto";
}



