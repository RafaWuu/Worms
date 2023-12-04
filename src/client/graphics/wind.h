#ifndef CLIENT_WIND_H
#define CLIENT_WIND_H

#include <SDL2pp/SDL2pp.hh>

#include "entity.h"
#include "texture_controller.h"
#include "configuration/configuration.h"

class Wind {
private:
    TextureController& texture_controller;

    std::shared_ptr<SDL2pp::Texture> left_wind;
    std::shared_ptr<SDL2pp::Texture> right_wind;

    float wind;

    float min_wind;
    float max_wind;

    int numFrames;
    int size;

    int x;
    int y;

public:
    Wind(TextureController& texture_controller, float wind);
    
    void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera);

    void change_wind(float wind);
};

#endif 
