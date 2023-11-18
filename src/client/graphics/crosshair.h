#include "animation.h"

class Crosshair : public Animation {
public:
    Crosshair(std::shared_ptr<SDL2pp::Texture> texture, TextureController& controller)
        : Animation(texture, controller) {}

    void render_crosshair(SDL2pp::Renderer& renderer, int player_x, int player_y, float aim_angle);
};
