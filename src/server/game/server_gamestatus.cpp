//
// Created by xguss on 02/11/23.
//

#include "server_gamestatus.h"

GameStatus::GameStatus(GameWorld& world): entities_info(world.get_entities_info()) {}

GameStatusError::GameStatusError(uint8_t code, GameWorld& world): code(code), GameStatus(world) {}

void GameStatusError::serialize(ServerProtocol& protocol) { protocol.send_game_errormessage(code); }


GameStatusScenario::GameStatusScenario(GameWorld& world): GameStatus(world) {
    height = width = 0;
    world.get_dimensions(height, width);
}

void GameStatusScenario::serialize(ServerProtocol& protocol) {
    protocol.send_scenario(entities_info, height, width);
}

GameStatusStart::GameStatusStart(GameWorld& world):
        worms_info(world.get_worms_info()), GameStatus(world) {}

void GameStatusStart::serialize(ServerProtocol& protocol) { protocol.send_worms_list(worms_info); }

GameStatusRunning::GameStatusRunning(GameWorld& world): GameStatus(world) {
    current_worm = world.get_active_worm();
    wind = world.get_wind_value();
    remaining_round_time = world.get_round_remaining_time();
}

void GameStatusRunning::serialize(ServerProtocol& protocol) {
    protocol.send_status(current_worm, remaining_round_time, wind, entities_info);
}
