#ifndef AIM_INFO_H
#define AIM_INFO_H

// ANGLE == mira; COORDINATES == teledirigido 
enum AimType {
    ANGLE,
    COORDINATES,
};

class AimInfo {
    float angle;
    float x;
    float y;

    AimType type; 

public:
    AimInfo(float angle, float pos_x, float pos_y, AimType type);

    AimType get_type();

    float get_angle();
    float get_x();
    float get_y();


};

#endif
