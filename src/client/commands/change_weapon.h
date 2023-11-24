#ifndef WORMS_CLIENT_CHANGE_WEAPON_H
#define WORMS_CLIENT_CHANGE_WEAPON_H

#include "client_command.h"

class ChangeWeapon : public Command{
private:
    int weapon_id;
public:
    ChangeWeapon(int weapon_id);
    void serialize(ClientProtocol& protocol) override;
};

#endif  // WORMS_CLIENT_CHANGE_WEAPON_H
