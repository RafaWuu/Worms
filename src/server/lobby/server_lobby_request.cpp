//
// Created by xguss on 01/11/23.
//

#include "server_lobby_request.h"

#include <memory>
#include <string>

#include "server_lobby_response.h"

LobbyRequestNewGame::LobbyRequestNewGame(const std::string&& s): scenario(s) {}

std::shared_ptr<Game> LobbyRequestNewGame::execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                                   uint16_t client_id) {

    uint16_t id = lobby.create_game(this->scenario, client_id);
    auto game = lobby.join_game(client_id, id);

    auto response = LobbyResponseGame(id);
    response.send(gp);

    return game;
}

LobbyRequestJoinGame::LobbyRequestJoinGame(uint16_t id): id(id) {}

std::shared_ptr<Game> LobbyRequestJoinGame::execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                                    uint16_t client_id) {
    auto game = lobby.join_game(client_id, id);

    auto response = LobbyResponseGame(id);
    response.send(gp);

    return game;
}

std::shared_ptr<Game> LobbyRequestListGames::execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                                     uint16_t client_id) {

    auto games = lobby.list_games();

    auto response = LobbyResponseGamesList(games);
    response.send(gp);

    return nullptr;
}
