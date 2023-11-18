#include <gtest/gtest.h>
#include <gmock/gmock-cardinalities.h>
#include "../src/common/common_baseprotocol_mock.h"
#include "../src/client/client_protocol.h"

using ::testing::AtLeast;
using ::testing::SetArgReferee;

TEST(ClientLobbyProtocol, SendCreateGameRequest) {
    MockBaseProtocol protocol;

    std::string escenario("basic");
    std::vector<char> nombre_escenario(escenario.begin(), escenario.end());

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SENDING))
        .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(CREATE_CODE))
        .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(escenario.length()))
        .Times(1);

    EXPECT_CALL(protocol, send_char_vector(nombre_escenario))
        .Times(1);    

    ClientProtocol client_protocol(protocol);
    client_protocol.send_create_game(escenario);
}

TEST(ClientLobbyProtocol, SendJoinGameRequest) {
    MockBaseProtocol protocol;

    int id = 1;

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SENDING))
        .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(JOIN_CODE))
        .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(id))
        .Times(1);

    ClientProtocol client_protocol(protocol);
    client_protocol.send_join_game(id);
}

TEST(ClientLobbyProtocol, SendGameListRequest) {
    MockBaseProtocol protocol;

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SENDING))
        .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(GAME_LIST_CODE))
        .Times(1);

    ClientProtocol client_protocol(protocol);
    client_protocol.request_game_list();
}

TEST(ClientLobbyProtocol, SendStartGame) {
    MockBaseProtocol protocol;

    EXPECT_CALL(protocol, send_1byte_number(GAME_SENDING))
        .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(START_GAME_CODE))
        .Times(1);

    ClientProtocol client_protocol(protocol);
    client_protocol.send_start_game();
}


TEST(ClientGameProtocol, ReceiveWorm) {
    MockBaseProtocol protocol;

    uint16_t id = 1;
    float x = 2.0;
    float y = 4.0;
    uint8_t dir = 0;
    uint16_t state = 0x004;
    uint8_t health = 10;
    uint8_t current_weapon = 1;
    float angle = M_PI;
    uint8_t power = 255;

    EXPECT_CALL(protocol, recv_2byte_number)
        .WillOnce(SetArgReferee<0, uint16_t>(1))
        .WillOnce(SetArgReferee<0, uint16_t>(0x004));

    EXPECT_CALL(protocol, recv_4byte_float)
        .WillOnce(SetArgReferee<0, float>(2.0f))
        .WillOnce(SetArgReferee<0, float>(4.0f))
            .WillOnce(SetArgReferee<0, float>(M_PI));

    EXPECT_CALL(protocol, recv_1byte_number)
        .WillOnce(SetArgReferee<0, uint8_t>(0))
        .WillOnce(SetArgReferee<0, uint8_t>(10))
        .WillOnce(SetArgReferee<0, uint8_t>(1))
        .WillOnce(SetArgReferee<0, uint8_t>(255));

    ClientProtocol client_protocol(protocol);
    Worm worm = *client_protocol.receive_worm();

    EXPECT_EQ(worm.get_id(), id);
    EXPECT_EQ(worm.get_pos_x(), x);
    EXPECT_EQ(worm.get_pos_y(), y);
    EXPECT_EQ(worm.get_dir(), dir);
    EXPECT_EQ(worm.get_state(), state);
    EXPECT_EQ(worm.get_health(), health);
}