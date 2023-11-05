//
// Created by xguss on 02/11/23.
//

#include "server_gamestatus.h"

GameStatus::GameStatus(GameWorld& world): worm_info(world.get_worms_info()) {}

GameStatusError::GameStatusError(uint8_t code, GameWorld& world): code(code), GameStatus(world) {}

void GameStatusError::serialize(ServerProtocol& protocol) { protocol.send_game_errormessage(code); }


GameStatusScenario::GameStatusScenario(GameWorld& world):
        beam_info(world.get_beams_info()), GameStatus(world) {}

void GameStatusScenario::serialize(ServerProtocol& protocol) {
    protocol.send_scenario(beam_info, worm_info);
}

GameStatusStart::GameStatusStart(GameWorld& world): GameStatus(world) {}

void GameStatusStart::serialize(ServerProtocol& protocol) { protocol.send_worms_list(worm_info); }

GameStatusRunning::GameStatusRunning(uint8_t current_worm, GameWorld& world):
        current_worm(current_worm), GameStatus(world) {}

void GameStatusRunning::serialize(ServerProtocol& protocol) {
    protocol.send_status(current_worm, worm_info);
}
