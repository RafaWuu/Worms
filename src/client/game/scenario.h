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

    std::vector<Worm> get_worms();
    std::vector<Beam> get_beams();
};

#endif
