#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2pp/SDL2pp.hh>

class Camera {
    SDL2pp::Rect camera;

public:
    Camera(int screen_width, int screen_height);
    
    void update(int x, int y, int w, int h);

    int get_x();
    int get_y();
};

#endif
