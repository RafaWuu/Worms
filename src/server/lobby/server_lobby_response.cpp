//
// Created by xguss on 01/11/23.
//

#include "server_lobby_response.h"

#include <vector>

LobbyResponseError::LobbyResponseError(uint8_t code): code(code) {}

void LobbyResponseError::send(ServerProtocol& gp) { gp.send_lobby_errormessage(this->code); }

LobbyResponseGame::LobbyResponseGame(uint16_t id): id(id) {}

void LobbyResponseGame::send(ServerProtocol& gp) { gp.send_gameid_message(id); }

LobbyResponseGamesList::LobbyResponseGamesList(std::vector<GameInfo>& games): games(games) {}

void LobbyResponseGamesList::send(ServerProtocol& gp) { gp.send_gameslist(games); }
