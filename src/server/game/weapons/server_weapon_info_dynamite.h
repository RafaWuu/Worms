

#ifndef WORMS_SERVER_WEAPON_INFO_DYNAMITE_H
#define WORMS_SERVER_WEAPON_INFO_DYNAMITE_H

#include "server_weapon_dynamite.h"
#include "server_weapon_info.h"

class DynamiteWeaponInfo: public WeaponInfo {
private:
    int ammo;
    float countdown;

public:
    explicit DynamiteWeaponInfo(const DynamiteWeapon& dynamite);
    void serialize_status(BaseProtocol& bp) override;
};


#endif  // WORMS_SERVER_WEAPON_INFO_DYNAMITE_H
