//
// Created by xguss on 05/11/23.
//

#ifndef WORMS_SERVER_ONFLOOR_CONTACTLISTENER_H
#define WORMS_SERVER_ONFLOOR_CONTACTLISTENER_H


#include "b2_contact.h"
#include "b2_world_callbacks.h"

class GameWorld;

// revised implementation of contact listener
class OnFloorContactListener: public b2ContactListener {
private:
    GameWorld& world;
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

public:
    explicit OnFloorContactListener(GameWorld& world);
    OnFloorContactListener(const OnFloorContactListener&) = delete;
    OnFloorContactListener& operator=(const OnFloorContactListener&) = delete;
};
#endif  // WORMS_SERVER_ONFLOOR_CONTACTLISTENER_H
