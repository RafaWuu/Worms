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
};

#endif
