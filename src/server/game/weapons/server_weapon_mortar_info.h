

#ifndef WORMS_SERVER_WEAPON_MORTAR_INFO_H
#define WORMS_SERVER_WEAPON_MORTAR_INFO_H

#include "server_weapon_info.h"
#include "server_weapon_mortar.h"

class MortarWeaponInfo: public WeaponInfo {
private:
    float angle;
    float power;
    int ammo;

public:
    explicit MortarWeaponInfo(const MortarWeapon& mortar);
    void serialize_status(BaseProtocol& bp) override;
};
#endif  // WORMS_SERVER_WEAPON_MORTAR_INFO_H
