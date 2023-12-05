

#include "server_provision_factory.h"

#include <memory>
#include <vector>

#include "../world/server_gameworld.h"
#include "game/listeners/server_explosion_callback.h"
#include "game/listeners/server_raycast_floor_calbback.h"

#include "common_weapon_constants.h"
#include "server_provision_effect_ammo.h"
#include "server_provision_effect_explosion.h"
#include "server_provision_effect_health.h"

#define RAY_LENGTH 25

#define MAX_TRIES 15

#define DOWN 0, -1

#define NO_VALID_X (-1)

#define Y_ORIGIN (-1)

ProvisionFactory::ProvisionFactory(GameWorld& world):
        world(world), rd(), gen(rd()), dis(0.0, 1.0), config(Configuration::get_instance()) {}

bool ProvisionFactory::provision_this_round() {
    auto u = dis(gen);

    if (u < config.provision_per_round)
        return true;
    return false;
}

std::shared_ptr<Provision> ProvisionFactory::generate_provision() {
    auto u = dis(gen);

    float x = find_valid_x();

    if (x == NO_VALID_X)
        return nullptr;

    if (u < config.kit_proportion) {
        return std::make_shared<Provision>(
                world, x, Y_ORIGIN, std::make_unique<ProvisionEffectHealth>(config.kit_health));
    }

    if (u < (config.ammo_box_proportion + config.kit_proportion)) {
        auto v = config.get_weapons_with_limited_ammo();
        std::vector<uint16_t> out;

        std::sample(v.begin(), v.end(), std::back_inserter(out), 1,
                    std::mt19937{std::random_device{}()});

        int quantity = ceil(config.get_weapon_ammo(config.get_weapon_name(out[0])) *
                            config.provision_ammo_amount);
        return std::make_shared<Provision>(world, x, Y_ORIGIN,
                                           std::make_unique<ProvisionEffectAmmo>(quantity, out[0]));
    }

    return std::make_shared<Provision>(
            world, x, Y_ORIGIN,
            std::make_unique<ProvisionEffectExplosion>(BAZOOKA_ID, config.provision_damage,
                                                       config.provision_radius,
                                                       config.provision_blast_power));
}

float ProvisionFactory::find_valid_x() {
    float y_ceil;
    float x_max;

    world.get_dimensions(y_ceil, x_max);

    double grid[MAX_TRIES] = {};

    for (double& i: grid) {
        auto u = dis(gen) * x_max;
        i = u;
    }

    b2Vec2 rayDir(DOWN);

    for (double& i: grid) {
        b2Vec2 center(i, Y_ORIGIN);

        b2Vec2 rayEnd = center + y_ceil * rayDir;

        // check what this ray hits
        RayCastFloorCallback callback;
        world.b2_world.RayCast(&callback, center, rayEnd);
        if (callback.m_body && callback.floor_was_hit) {
            return i;
        }
    }

    return NO_VALID_X;
}
