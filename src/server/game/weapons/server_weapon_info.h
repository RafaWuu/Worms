//
// Created by xguss on 26/11/23.
//

#ifndef WORMS_SERVER_WEAPON_INFO_H
#define WORMS_SERVER_WEAPON_INFO_H

#include "common_baseprotocol.h"

class WeaponInfo {
public:
    virtual ~WeaponInfo() = default;
    virtual void serialize_status(BaseProtocol& bp) = 0;
};
#endif  // WORMS_SERVER_WEAPON_INFO_H
