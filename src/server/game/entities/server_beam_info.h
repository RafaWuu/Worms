//
// Created by xguss on 03/11/23.
//

#ifndef WORMS_SERVER_BEAM_INFO_H
#define WORMS_SERVER_BEAM_INFO_H

#include "server_gameobject_info.h"
#include "server_beam.h"

class BeamInfo : public GameObjectInfo {
public:
    explicit BeamInfo(const Beam& beam);
    const Beam& beam;

    void serialize_scenario(ServerProtocol &gp) override;
    void serialize_status(ServerProtocol &gp) override;
};
#endif  // WORMS_SERVER_BEAM_INFO_H
