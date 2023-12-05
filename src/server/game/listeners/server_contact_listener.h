

#ifndef WORMS_SERVER_CONTACT_LISTENER_H
#define WORMS_SERVER_CONTACT_LISTENER_H


#include "b2_contact.h"
#include "b2_world_callbacks.h"

class GameWorld;

// revised implementation of contact listener
class ContactListener: public b2ContactListener {
private:
    GameWorld& world;
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

public:
    explicit ContactListener(GameWorld& world);
    ContactListener(const ContactListener&) = delete;
    ContactListener& operator=(const ContactListener&) = delete;
};
#endif  // WORMS_SERVER_CONTACT_LISTENER_H
