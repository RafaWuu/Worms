//
// Created by xguss on 02/11/23.
//

#include "server_gameevent.h"

void GameEventStartGame::execute(EventHandler& e) { e.create_game(this->client_id); }

GameEventStartGame::GameEventStartGame(uint16_t client_id): GameEvent(client_id) {}

GameEventMove::GameEventMove(uint16_t client_id, uint8_t worm_id, MovementEnum code):
        worm_id(worm_id), code(code), GameEvent(client_id) {}

void GameEventMove::execute(EventHandler& e) {
    e.move_worm(this->client_id, this->worm_id, this->code);
}
