//
// Created by xguss on 15/11/23.
//

#include <gtest/gtest.h>
#include <gmock/gmock-cardinalities.h>
#include "../src/common/common_baseprotocol_mock.h"
#include "../src/server/server_protocol.h"
#include "../src/server/lobby/server_lobby_request.h"
#include "../src/server/server_error.h"
#include "common_weapon_constants.h"
#include "game/entities/server_worm_info.h"
#include "game/weapons/server_weapon_info_bazooka.h"


using ::testing::AtLeast;
using ::testing::SetArgReferee;

// Lobby envia nuevo cliente

TEST(ServerLobbyTest, LobbyCanSendNewClient) {
    MockBaseProtocol protocol;

    uint16_t id = 6;

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SENDING))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_NEWCLIENT))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(id))
            .Times(1);

    ServerProtocol serverProtocol(protocol);
    serverProtocol.send_lobby_newclient(id);
}

// Lobby envia error

TEST(ServerLobbyTest, LobbyCanSendError) {
    MockBaseProtocol protocol;

    uint8_t id = 5;

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SENDING))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_ERROR))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(id))
            .Times(1);

    ServerProtocol serverProtocol(protocol);

    serverProtocol.send_lobby_errormessage(id);
}

// Lobby envia id de partida al unirse correctamente

TEST(ServerLobbyTest, LobbyCanSendId) {
    MockBaseProtocol protocol;

    uint16_t id = 1;

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SENDING))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_GAMEJOINING))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(id))
            .Times(1);

    ServerProtocol serverProtocol(protocol);

    serverProtocol.send_gameid_message(id);
}


// Lobby envia lista de partidas

TEST(ServerLobbyTest, LobbyCanSendGamesList) {
    MockBaseProtocol protocol;

    std::vector<GameInfo> games_vec;

    uint16_t game_id = 2;
    std::string game_name = "basic";
    std::vector<char> vector(game_name.begin(), game_name.end());

    games_vec.emplace_back(game_id, game_name, 3, 5, false);

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SENDING))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_GAMELISTING))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(games_vec.size()))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(game_id))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(game_name.length()))
            .Times(1);

    EXPECT_CALL(protocol, send_char_vector(vector))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(3))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(5))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(0))
            .Times(1);

    ServerProtocol serverProtocol(protocol);
    serverProtocol.send_gameslist(games_vec);
}

// Lobby envia lista de escenarios

TEST(ServerLobbyTest, LobbyCanSendScenariosList) {
    MockBaseProtocol protocol;

    std::map<std::string, uint16_t> map;


    std::string game_name = "basic";
    uint16_t worms = 12;

    std::vector<char> vector(game_name.begin(), game_name.end());

    map.emplace(game_name, worms);

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SENDING))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SCENARIOLISTING))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(map.size()))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(game_name.length()))
            .Times(1);

    EXPECT_CALL(protocol, send_char_vector(vector))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(worms))
            .Times(1);

    ServerProtocol serverProtocol(protocol);
    serverProtocol.send_scenarioslist(map);
}


// Lobby envia lista de escenarios

TEST(ServerLobbyTest, LobbyCanSendScenario) {
    MockBaseProtocol protocol;

    std::map<std::string, uint16_t> map;


    std::string game_name = "basic";
    uint16_t worms = 12;

    std::vector<char> vector(game_name.begin(), game_name.end());

    map.emplace(game_name, worms);

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SENDING))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(LOBBY_SCENARIOLISTING))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(map.size()))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(game_name.size()))
            .Times(1);

    EXPECT_CALL(protocol, send_char_vector(vector))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(worms))
            .Times(1);



    ServerProtocol serverProtocol(protocol);
    serverProtocol.send_scenarioslist(map);
}

// Lobby devuelve error cuando el mensaje es invalido

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

// Lobby devuelve error cuando el mensaje de creacion de partida es invalido

TEST(ServerLobbyTest, LobbyThrowOnInvalidCreateGameRequest) {
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

// Lobby crea correctamente una partida a par

TEST(ServerLobbyTest, LobbyCanCreateGame) {
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

// Lobby se une  correctamente una partida

TEST(ServerLobbyTest, LobbyCanJoinGame) {
    MockBaseProtocol protocol;

    uint16_t id = 12;

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(LOBBY_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(JOIN_GAME));

    EXPECT_CALL(protocol, recv_2byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(id));


    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<LobbyRequest> req = serverProtocol.recv_lobby_msg();

    LobbyRequestJoinGame* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<LobbyRequestJoinGame*>(req.get()))
                                << "No se creo la peticion del tipo adecuado";

    EXPECT_EQ(id, req2->id) << "id de partida incorrecto";
}

// Lobby acepta pedido de lista de partidas

TEST(ServerLobbyTest, LobbyCanListGames) {
    MockBaseProtocol protocol;

    uint16_t id = 12;

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(LOBBY_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(LIST_GAMES));

    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<LobbyRequest> req = serverProtocol.recv_lobby_msg();

    LobbyRequestListGames* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<LobbyRequestListGames*>(req.get()))
                                << "No se creo la peticion del tipo adecuado";
}


// Lobby acepta pedido de lista de escenarios

TEST(ServerLobbyTest, LobbyCanListScenarios) {
    MockBaseProtocol protocol;

    uint16_t id = 12;

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(LOBBY_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(LIST_SCENARIOS));

    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<LobbyRequest> req = serverProtocol.recv_lobby_msg();

    LobbyRequestListScenarios* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<LobbyRequestListScenarios*>(req.get()))
                                << "No se creo la peticion del tipo adecuado";
}


// Game recibe pedido de iniciar partida

TEST(ServerGameTest, GameCanStartGame) {
    MockBaseProtocol protocol;

    uint16_t id = 12;

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(GAME_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(StartGame));

    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<GameEvent> req = serverProtocol.recv_game_msg(id);

    GameEventStartGame* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<GameEventStartGame*>(req.get()))
                                << "No se creo la peticion del tipo adecuado";
}

// Game recibe pedido de frenar worm

TEST(ServerGameTest, GameCanStopWorm) {
    MockBaseProtocol protocol;

    uint16_t id = 12;
    uint8_t id_worm = 15;
    uint8_t code = MoveEnum::StopMove;

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(GAME_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(Input::Move))
            .WillOnce(SetArgReferee<0>(id_worm))
            .WillOnce(SetArgReferee<0>(code));


    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<GameEvent> req = serverProtocol.recv_game_msg(id);

    GameEventStop* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<GameEventStop*>(req.get()))
                                << "No se creo la peticion del tipo adecuado";

    EXPECT_EQ(id_worm, req2->worm_id) << "id de worm incorrecto";
}

// Game recibe pedido de mover worm

TEST(ServerGameTest, GameCanMoveWorm) {
    MockBaseProtocol protocol;

    uint16_t id = 12;
    uint8_t id_worm = 15;
    uint8_t code = MoveEnum::MoveRight;

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(GAME_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(Input::Move))
            .WillOnce(SetArgReferee<0>(id_worm))
            .WillOnce(SetArgReferee<0>(code));


    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<GameEvent> req = serverProtocol.recv_game_msg(id);

    GameEventMove* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<GameEventMove*>(req.get()))
                                << "No se creo la peticion del tipo adecuado";

    EXPECT_EQ(id_worm, req2->worm_id) << "id de worm incorrecto";
    EXPECT_EQ(DirRight, req2->dir) << "direccion de worm incorrecto";
}

// Game recibe pedido de saltar worm

TEST(ServerGameTest, GameCanJumpWorm) {
    MockBaseProtocol protocol;

    uint16_t id = 12;
    uint8_t id_worm = 15;

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(GAME_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(Input::Jump))
            .WillOnce(SetArgReferee<0>(id_worm));

    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<GameEvent> req = serverProtocol.recv_game_msg(id);

    GameEventJump* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<GameEventJump*>(req.get()))
                                << "No se creo la peticion del tipo adecuado";

    EXPECT_EQ(id_worm, req2->worm_id) << "id de worm incorrecto";
}

// Game recibe pedido de dar la vuelta al worm

TEST(ServerGameTest, GameCanRollbackWorm) {
    MockBaseProtocol protocol;

    uint16_t id = 12;
    uint8_t id_worm = 15;

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(GAME_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(Input::Rollback))
            .WillOnce(SetArgReferee<0>(id_worm));

    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<GameEvent> req = serverProtocol.recv_game_msg(id);

    GameEventRollBack* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<GameEventRollBack*>(req.get()))
                                << "No se creo la peticion del tipo adecuado";

    EXPECT_EQ(id_worm, req2->worm_id) << "id de worm incorrecto";
}

// Game recibe pedido de disparar al worm

TEST(ServerGameTest, GameCanFireWormWeapon) {
    MockBaseProtocol protocol;

    uint16_t id = 12;
    uint8_t id_worm = 15;

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(GAME_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(Input::Fire))
            .WillOnce(SetArgReferee<0>(id_worm));

    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<GameEvent> req = serverProtocol.recv_game_msg(id);

    GameEventFireGun* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<GameEventFireGun*>(req.get()))
                                << "No se creo la peticion del tipo adecuado";

    EXPECT_EQ(id_worm, req2->worm_id) << "id de worm incorrecto";
}

// Game recibe pedido de apuntar

TEST(ServerGameTest, GameCanAimWorm) {
    MockBaseProtocol protocol;

    uint16_t id = 12;
    uint8_t id_worm = 15;

    EXPECT_CALL(protocol, recv_1byte_number)
            .WillOnce(SetArgReferee<0, uint8_t>(GAME_RECEIVING))
            .WillOnce(SetArgReferee<0, uint8_t>(Input::Aim))
            .WillOnce(SetArgReferee<0>(id_worm))
            .WillOnce(SetArgReferee<0>(AimType::AimUp));

    EXPECT_CALL(protocol, recv_4byte_float)
            .WillOnce(SetArgReferee<0, float>(2))
            .WillOnce(SetArgReferee<0, float>(3));

    ServerProtocol serverProtocol(protocol);

    std::unique_ptr<GameEvent> req = serverProtocol.recv_game_msg(id);

    GameEventAim* req2;
    ASSERT_NO_THROW(req2 = dynamic_cast<GameEventAim*>(req.get()))
                                << "No se creo la peticion del tipo adecuado";

    EXPECT_EQ(id_worm, req2->worm_id) << "id de worm incorrecto";
    EXPECT_EQ(2, req2->x) << "Posicion incorrecta";
    EXPECT_EQ(3, req2->y) << "Posicion incorrecta";
}


// Lobby envia lista de partidas

TEST(ServerGameTest, GameCanSendWormStatus) {
    MockBaseProtocol protocol;

    std::vector<GameInfo> games_vec;

    uint16_t current_worm = 16;
    float time = 27;
    float wind = 15;

    std::map<uint16_t, std::shared_ptr<GameObjectInfo>> entities;

    entities.emplace(3, std::make_shared<WormInfo>(WORM, 5,7, 3, true, Active, 100, BAZOOKA_ID, 65,
                                                   std::make_unique<BazookaWeaponInfo>(413, .3, 120)));

    EXPECT_CALL(protocol, send_1byte_number(GAME_SENDING))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(GAME_STATUS))
            .Times(2);

    EXPECT_CALL(protocol, send_2byte_number(current_worm))
            .Times(1);

    EXPECT_CALL(protocol, send_4byte_float(time))
            .Times(1);

    EXPECT_CALL(protocol, send_4byte_float(wind))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(entities.size()))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(3))
            .Times(2);

    EXPECT_CALL(protocol, send_4byte_float(5))
            .Times(1);

    EXPECT_CALL(protocol, send_4byte_float(7))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(true))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(Active))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(100))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(BAZOOKA_ID))
            .Times(1);

    EXPECT_CALL(protocol, send_2byte_number(120))
            .Times(1);

    EXPECT_CALL(protocol, send_4byte_float(413))
            .Times(1);

    EXPECT_CALL(protocol, send_1byte_number(.3 * 255))
            .Times(1);

    ServerProtocol serverProtocol(protocol);
    serverProtocol.send_status(current_worm, time, wind, entities);
}