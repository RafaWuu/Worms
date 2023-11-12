#ifndef CLIENT_BEAM_H
#define CLIENT_BEAM_H

class Beam {
private:
    float x;
    float y;
    float height;
    float width;
    float angle;
public:
    explicit Beam(float x, float y, float height, float width, float angle);
    float get_pos_x();
    float get_pos_y();
    float get_height();
    float get_width();
    float get_angle();
};

#endif
