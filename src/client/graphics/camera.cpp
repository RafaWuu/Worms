#include "camera.h"

#include "client_constants.h"

Camera::Camera(int width, int height) : camera(0, 0, width, height) {}

void Camera::update(int x, int y, int w, int h) {
    camera.x = (x + w / 2)  - SCREEN_WIDTH / 2;
    camera.y = ((-1) * y + h / 2)  - SCREEN_HEIGHT / 2;

    if (camera.x < 0)
        camera.x = 0;

    if (camera.y < 0)
        camera.y = 0;
}

int Camera::get_x() {
    return camera.x;
}

int Camera::get_y() {
    return camera.y;
}