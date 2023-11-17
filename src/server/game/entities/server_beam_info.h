//
// Created by xguss on 03/11/23.
//

#ifndef WORMS_SERVER_BEAM_INFO_H
#define WORMS_SERVER_BEAM_INFO_H

#include "server_beam.h"
#include "server_gameobject_info.h"

class BeamInfo: public GameObjectInfo {
public:
    explicit BeamInfo(const Beam& beam);
    const Beam& beam;

    void serialize_scenario(BaseProtocol& bp) override;
    void serialize_status(BaseProtocol& gp) override;
};
#endif  // WORMS_SERVER_BEAM_INFO_H
