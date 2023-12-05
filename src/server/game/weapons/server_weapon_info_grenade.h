

#ifndef WORMS_SERVER_WEAPON_INFO_GRENADE_H
#define WORMS_SERVER_WEAPON_INFO_GRENADE_H

#include "server_weapon_grenade.h"
#include "server_weapon_info.h"

class GrenadeWeaponInfo: public WeaponInfo {
private:
    float angle;
    float power;
    float countdown;

public:
    explicit GrenadeWeaponInfo(const GrenadeWeapon& grenade);
    void serialize_status(BaseProtocol& bp) override;
};
#endif  // WORMS_SERVER_WEAPON_INFO_GRENADE_H
