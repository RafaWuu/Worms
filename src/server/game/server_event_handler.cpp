//
// Created by xguss on 02/11/23.
//

#include "server_event_handler.h"

#include <memory>
#include <vector>

#include "server_error.h"

EventHandler::EventHandler(GameWorld& game_world, StatusBroadcastMonitor& broadcast,
                           std::vector<uint16_t>& id_list, bool& had_started, uint16_t& game_owner):
        game_world(game_world),
        id_list(id_list),
        had_started(had_started),
        broadcast(broadcast),
        game_owner(game_owner) {}

void EventHandler::move_worm(uint16_t client_id, uint8_t worm_id, InputEnum code) {
    if (!had_started)
        throw GameHasNotStartedGameError(client_id);

    Worm* worm = game_world.get_worm(worm_id);

    if (!worm)
        throw InvalidWormIdGameError(client_id);

    worm->handle_input(client_id, code);
}

void EventHandler::create_game(uint16_t client_id) {
    if (client_id != game_owner)
        throw OnlyTheOwnerCanLaunchGameError(client_id);

    game_world.set_clients_to_worms(id_list);
    broadcast.send_status_toall(std::make_shared<GameStatusStart>(game_world));
    had_started = true;
}
