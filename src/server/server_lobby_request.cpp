//
// Created by xguss on 01/11/23.
//

#include "server_lobby_request.h"

#include <memory>
#include <string>

#include "server_lobby_answer.h"

LobbyRequestNewGame::LobbyRequestNewGame(const std::string& s): scenario(s) {}

std::unique_ptr<Game> LobbyRequestNewGame::execute(Lobby& lobby, ServerProtocol& gp) {
    try {
        size_t id = lobby.create_game(this->scenario);
        auto game = lobby.join_game(id);

        auto answer = LobbyAnswerGame(id);
        answer.send(gp);

        return game;
    } catch (std::exception& e) {
        auto answer = LobbyAnswerError(1);
        answer.send(gp);

        return nullptr;
    }
}

LobbyRequestJoinGame::LobbyRequestJoinGame(size_t id): id(id) {}

std::unique_ptr<Game> LobbyRequestJoinGame::execute(Lobby& lobby, ServerProtocol& gp) {
    try {
        auto game = lobby.join_game(id);

        auto answer = LobbyAnswerGame(id);
        answer.send(gp);

        return game;
    } catch (std::exception& e) {
        auto answer = LobbyAnswerError(1);
        answer.send(gp);

        return nullptr;
    }
}

std::unique_ptr<Game> LobbyRequestListGames::execute(Lobby& lobby, ServerProtocol& gp) {
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
