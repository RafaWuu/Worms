//
// Created by xguss on 30/11/23.
//

#ifndef WORMS_SERVER_PROVISION_FACTORY_H
#define WORMS_SERVER_PROVISION_FACTORY_H

#include <memory>
#include <random>

#include "../../../../configuration/configuration.h"

#include "server_provision.h"

class ProvisionFactory {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
    std::uniform_int_distribution<> dis_sample;

    Configuration& config;

    GameWorld& world;

public:
    explicit ProvisionFactory(GameWorld& world);

    bool provision_this_round();

    std::shared_ptr<Provision> generate_provision();

    float find_valid_x();
};
#endif  // WORMS_SERVER_PROVISION_FACTORY_H
