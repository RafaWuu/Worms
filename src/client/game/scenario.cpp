#include "scenario.h"


Scenario::Scenario(std::vector<Beam> beams, std::vector<Worm> worms) : beams(beams), worms(worms) {}

std::vector<Worm> Scenario::get_worms() {
    return worms;
}