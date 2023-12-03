//
// Created by xguss on 28/11/23.
//

#ifndef WORMS_SERVER_GAMEWORLD_STATE_H
#define WORMS_SERVER_GAMEWORLD_STATE_H

#include <map>
#include <memory>

#include "game/entities/server_worm.h"
#include "game/provisions/server_provision_factory.h"

#include "server_player_manager.h"

class GameWorldState {
protected:
    PlayerManager& player_manager;
    GameWorld& world;

public:
    GameWorldState(PlayerManager& player_manager, GameWorld& world);
    virtual ~GameWorldState() = default;
    virtual std::unique_ptr<GameWorldState> update() = 0;
    virtual void handle_worm_damaged(uint16_t worm_id) = 0;

    virtual void handle_weapon_fired() = 0;

    virtual void handle_entity_moving() = 0;

    virtual Worm& get_active_worm() = 0;
};

#endif  // WORMS_SERVER_GAMEWORLD_STATE_H
