#ifndef WORM_H
#define WORM_H

#include <string>
#include <SDL2pp/SDL2pp.hh>

class Worm {
private:
    int8_t id;
    float  pos_x;
    float  pos_y;
    int8_t state;
    int8_t health;   

public: 
    Worm(int8_t id, float pos_x, float pos_y, int8_t state, int8_t health);

    void set_position(float x, float y);
    void set_health(int8_t health);

    float get_pos_x();
    float get_pos_y();
};

#endif