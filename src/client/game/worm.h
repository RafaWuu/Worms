#ifndef WORM_H
#define WORM_H

#include <string>

#include <SDL2pp/SDL2pp.hh>

enum WORM_STATE { DirLeft = 1, DirRight = 2, Stop = 3, JumpF = 4, JumpB = 5 };

class Worm {
private:
    uint8_t id;
    float pos_x;
    float pos_y;
    uint8_t dir;
    uint16_t state;
    uint8_t health;

public:
    Worm(uint8_t id, float pos_x, float pos_y, uint8_t dir, uint16_t state, uint8_t health);

    void set_position(float x, float y);
    void set_health(int8_t health);

    float get_pos_x();
    float get_pos_y();
    int get_health();
    int get_state();
    int get_id() const;

    uint8_t get_dir() const;
};

#endif