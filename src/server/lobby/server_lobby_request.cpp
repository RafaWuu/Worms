//
// Created by xguss on 01/11/23.
//

#include "server_lobby_request.h"

#include <memory>
#include <string>

#include "server_lobby_answer.h"

LobbyRequestNewGame::LobbyRequestNewGame(const std::string& s): scenario(s) {}

std::shared_ptr<Game> LobbyRequestNewGame::execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                                   uint16_t client_id) {
    try {
        uint16_t id = lobby.create_game(this->scenario, client_id);
        auto game = lobby.join_game(id, client_id);

        auto answer = LobbyAnswerGame(id);
        answer.send(gp);

        return game;
    } catch (std::exception& e) {
        auto answer = LobbyAnswerError(1);
        answer.send(gp);

        return nullptr;
    }
}

LobbyRequestJoinGame::LobbyRequestJoinGame(uint16_t id): id(id) {}

std::shared_ptr<Game> LobbyRequestJoinGame::execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                                    uint16_t client_id) {
    try {
        auto game = lobby.join_game(id, client_id);

        auto answer = LobbyAnswerGame(id);
        answer.send(gp);

        return game;
    } catch (std::exception& e) {
        auto answer = LobbyAnswerError(1);
        answer.send(gp);

        return nullptr;
    }
}

std::shared_ptr<Game> LobbyRequestListGames::execute(LobbyMonitor& lobby, ServerProtocol& gp,
                                                     uint16_t client_id) {
    try {
        auto games = lobby.list_games();

        auto answer = LobbyAnswerGamesList(games);
        answer.send(gp);

        return nullptr;
    } catch (std::exception& e) {
        auto answer = LobbyAnswerError(1);
        answer.send(gp);

        return nullptr;
    }
}
