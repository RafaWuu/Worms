#include "animation.h"
#include "camera.h"

class Crosshair : public Animation {
public:
    Crosshair(std::shared_ptr<SDL2pp::Texture> texture, TextureController& controller)
        : Animation(texture, controller) {}

    void render_by_angle(SDL2pp::Renderer& renderer, int player_x, int player_y, float aim_angle, Camera& camera);

    // Dibuja el crosshair en la posicion pasada por parametro
    void render_by_coordinates(SDL2pp::Renderer& renderer, float x, float y, Camera& camera);
};
