

#ifndef WORMS_SERVER_WEAPON_INFO_AIRATTACK_H
#define WORMS_SERVER_WEAPON_INFO_AIRATTACK_H


#include "server_weapon_airattack.h"
#include "server_weapon_info.h"

class AirAttackWeaponInfo: public WeaponInfo {
private:
    float aim_x;
    float aim_y;
    int ammo;

public:
    explicit AirAttackWeaponInfo(const AirAttackWeapon& object);
    void serialize_status(BaseProtocol& bp) override;
};


#endif  // WORMS_SERVER_WEAPON_INFO_AIRATTACK_H
