#ifndef CLIENT_SCENARIO_H
#define CLIENT_SCENARIO_H

#include "beam.h"
#include "worm.h"
#include <vector>

class Scenario {
private:
    std::vector<Beam> beams;
    std::vector<Worm> worms;
public:
    Scenario(std::vector<Beam> beams, std::vector<Worm> worms);
};

#endif
