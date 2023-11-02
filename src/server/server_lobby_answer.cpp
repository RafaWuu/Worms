//
// Created by xguss on 01/11/23.
//

#include "server_lobby_answer.h"

#include <vector>

LobbyAnswerError::LobbyAnswerError(uint8_t code): code(code) {}

void LobbyAnswerError::send(ServerProtocol& gp) { gp.send_lobby_errormessage(this->code); }

LobbyAnswerGame::LobbyAnswerGame(size_t id): id(id) {}

void LobbyAnswerGame::send(ServerProtocol& gp) { gp.send_gameid_message(id); }

LobbyAnswerGamesList::LobbyAnswerGamesList(std::vector<GameInfo>& games): games(games) {}

void LobbyAnswerGamesList::send(ServerProtocol& gp) { gp.send_gameslist(games); }
