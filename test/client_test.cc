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


TEST(ProtocolReceiveWorm, ReceiveWormScopedWeapon) {
    MockBaseProtocol protocol;

    uint16_t id = 1;
    float x = 2.0;
    float y = 4.0;
    uint8_t dir = 0;
    uint16_t state = 0x004;
    uint8_t health = 10;
    uint8_t current_weapon = 0;
    uint16_t ammo = 20;

    float angle = M_PI;
    float x_aim = 0;
    float y_aim = 0;
    AimType aim_type = ANGLE;

    uint8_t power = 255;

    EXPECT_CALL(protocol, recv_2byte_number)
        .WillOnce(SetArgReferee<0, uint16_t>(1))
        .WillOnce(SetArgReferee<0, uint16_t>(0x004))
        .WillOnce(SetArgReferee<0, uint16_t>(20));

    EXPECT_CALL(protocol, recv_4byte_float)
        .WillOnce(SetArgReferee<0, float>(2.0f))
        .WillOnce(SetArgReferee<0, float>(- 4.0f))
        .WillOnce(SetArgReferee<0, float>(M_PI));

    EXPECT_CALL(protocol, recv_1byte_number)
        .WillOnce(SetArgReferee<0, uint8_t>(0))
        .WillOnce(SetArgReferee<0, uint8_t>(10))
        .WillOnce(SetArgReferee<0, uint8_t>(0))
        .WillOnce(SetArgReferee<0, uint8_t>(255));

    ClientProtocol client_protocol(protocol);
    Worm worm = *client_protocol.receive_worm();

    EXPECT_EQ(worm.get_id(), id);
    EXPECT_EQ(worm.get_pos_x(), x * SCALE);
    EXPECT_EQ(worm.get_pos_y(), y * SCALE);
    EXPECT_EQ(worm.get_dir(), dir);
    EXPECT_EQ(worm.get_state(), state);
    EXPECT_EQ(worm.get_current_weapon(), current_weapon);
    EXPECT_EQ(worm.get_aim_angle(), angle);
    EXPECT_EQ(worm.get_x_aim(), x_aim * SCALE);
    EXPECT_EQ(worm.get_y_aim(), y_aim * SCALE);
}

TEST(ProtocolReceiveWorm, ReceiveWormWeaponTeledirigido) {
    MockBaseProtocol protocol;

    uint16_t id = 1;
    float x = 2.0;
    float y = 4.0;
    uint8_t dir = 0;
    uint16_t state = 0x004;
    uint8_t health = 10;
    uint8_t current_weapon = 9;
    uint16_t ammo = 20;

    float angle = 0;
    float x_aim = 50;
    float y_aim = 20;
    AimType aim_type = ANGLE;

    uint8_t power = 0;

    EXPECT_CALL(protocol, recv_2byte_number)
        .WillOnce(SetArgReferee<0, uint16_t>(1))
        .WillOnce(SetArgReferee<0, uint16_t>(0x004))
        .WillOnce(SetArgReferee<0, uint16_t>(20));

    EXPECT_CALL(protocol, recv_4byte_float)
        .WillOnce(SetArgReferee<0, float>(2.0f))
        .WillOnce(SetArgReferee<0, float>(- 4.0f))
        .WillOnce(SetArgReferee<0, float>(50))
        .WillOnce(SetArgReferee<0, float>(-20));

    EXPECT_CALL(protocol, recv_1byte_number)
        .WillOnce(SetArgReferee<0, uint8_t>(0))
        .WillOnce(SetArgReferee<0, uint8_t>(10))
        .WillOnce(SetArgReferee<0, uint8_t>(9));

    ClientProtocol client_protocol(protocol);
    Worm worm = *client_protocol.receive_worm();

    EXPECT_EQ(worm.get_id(), id);
    EXPECT_EQ(worm.get_pos_x(), x * SCALE);
    EXPECT_EQ(worm.get_pos_y(), y * SCALE);
    EXPECT_EQ(worm.get_dir(), dir);
    EXPECT_EQ(worm.get_state(), state);
    EXPECT_EQ(worm.get_current_weapon(), current_weapon);
    EXPECT_EQ(worm.get_aim_angle(), angle);
    EXPECT_EQ(worm.get_x_aim(), x_aim * SCALE);
    EXPECT_EQ(worm.get_y_aim(), y_aim * SCALE);
}

TEST(ProtocolReceiveProjectile, ReceiveProjectile) {
    MockBaseProtocol protocol;

    uint8_t type = 0;
    float x = 10;
    float y = 15;
    float angle = 2;    

    EXPECT_CALL(protocol, recv_4byte_float)
        .WillOnce(SetArgReferee<0, float>(10))
        .WillOnce(SetArgReferee<0, float>(-15))
        .WillOnce(SetArgReferee<0, float>(2));

    EXPECT_CALL(protocol, recv_1byte_number)
        .WillOnce(SetArgReferee<0, uint8_t>(0));

    ClientProtocol client_protocol(protocol);
    Projectile projectile = *client_protocol.receive_projectile();

    EXPECT_EQ(projectile.type, type);
    EXPECT_EQ(projectile.get_angle(), angle);
    EXPECT_EQ(projectile.get_pos_x(), x * SCALE);
    EXPECT_EQ(projectile.get_pos_y(), y * SCALE);
}

TEST(ProtocolReceiveExplosion, RecieveExplosion) {
    MockBaseProtocol protocol;

    uint16_t type = 0;
    float x = 10;
    float y = 15;
    float radius = 2;    

    EXPECT_CALL(protocol, recv_4byte_float)
        .WillOnce(SetArgReferee<0, float>(2))
        .WillOnce(SetArgReferee<0, float>(10))
        .WillOnce(SetArgReferee<0, float>(-15));

    EXPECT_CALL(protocol, recv_2byte_number)
        .WillOnce(SetArgReferee<0, uint16_t>(0));

    ClientProtocol client_protocol(protocol);
    Explosion explosion = *client_protocol.receive_explosion();

    EXPECT_EQ(explosion.type, type);
    EXPECT_EQ(explosion.get_radius(), radius * SCALE);
    EXPECT_EQ(explosion.get_pos_x(), x * SCALE);
    EXPECT_EQ(explosion.get_pos_y(), y * SCALE);
}

TEST(ProtocolSerialize, SerializeMoveLeft) {
    MockBaseProtocol protocol;

    uint8_t worm = 0;
    uint8_t direction = 1;

    std::vector<uint8_t> serialized_command = {GAME_SENDING, MOVE_CODE, worm, direction};

    EXPECT_CALL(protocol, send_uint_vector(serialized_command))
        .Times(1);

    ClientProtocol client_protocol(protocol);
    client_protocol.serialize_move(0, direction);
}

TEST(ProtocolSerialize, SerializeMoveRight) {
    MockBaseProtocol protocol;

    uint8_t worm = 0;
    uint8_t direction = 0;

    std::vector<uint8_t> serialized_command = {GAME_SENDING, MOVE_CODE, worm, direction};

    EXPECT_CALL(protocol, send_uint_vector(serialized_command))
        .Times(1);

    ClientProtocol client_protocol(protocol);
    client_protocol.serialize_move(0, direction);
}

TEST(ProtocolSerialize, SerializeAim) {
    MockBaseProtocol protocol;

    uint8_t worm = 0;
    uint8_t aim = 1; // 1 si esta apuntando, 2 si deja de apuntar

    float x = 20;
    float y = 30;

    std::vector<uint8_t> serialized_command = {GAME_SENDING, AIM_CODE, worm, aim};

    EXPECT_CALL(protocol, send_uint_vector(serialized_command))
        .Times(1);

    EXPECT_CALL(protocol, send_4byte_float(x / SCALE))
        .Times(1);

    EXPECT_CALL(protocol, send_4byte_float(- y / SCALE))
        .Times(1);   

    ClientProtocol client_protocol(protocol);
    client_protocol.serialize_aim(0, x, y);
}

TEST(ProtocolSerialize, SerializeStopAim) {
    MockBaseProtocol protocol;

    uint8_t worm = 0;
    uint8_t aim = 2; // 1 si esta apuntando, 2 si deja de apuntar

    float x = 20;
    float y = 30;

    std::vector<uint8_t> serialized_command = {GAME_SENDING, AIM_CODE, worm, aim};

    EXPECT_CALL(protocol, send_uint_vector(serialized_command))
        .Times(1);  

    ClientProtocol client_protocol(protocol);
    client_protocol.serialize_stop_aim(0);
}

