/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include "animation.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include <SDL2pp/SDL2pp.hh>

Animation::Animation(std::shared_ptr<SDL2pp::Texture> texture, TextureController& controller):
        texture_controller(controller), texture(texture), currentFrame(0), elapsed(0.0f) {
    SDL2pp::Texture const& my_texture = *texture;
    numFrames = my_texture.GetHeight() / my_texture.GetWidth();
    size = my_texture.GetWidth();

    assert(this->numFrames > 0);
    assert(this->size > 0);
}

Animation::~Animation() {}

void Animation::update(float dt) {
    this->elapsed += dt;
    /* checks if the frame should be updated based on the time elapsed since the last update */
    while (this->elapsed > FRAME_RATE) {
        this->advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */
void Animation::render(SDL2pp::Renderer& renderer, const SDL2pp::Rect dst,
                       SDL_RendererFlip& flipType) {
    renderer.Copy(
            *texture,
            SDL2pp::Rect(0, 2 + this->size * this->currentFrame, this->size, this->size), dst,
            0.0,              // don't rotate
            SDL2pp::NullOpt,  // rotation center - not needed
            flipType);
}

void Animation::change_texture(AnimationState new_state) {
    std::shared_ptr<SDL2pp::Texture> new_texture = texture_controller.get_texture(new_state);
    texture = new_texture;

    // Los sprites pueden tener distintas dimensiones
    SDL2pp::Texture const& my_texture = *texture;
    numFrames = my_texture.GetHeight() / my_texture.GetWidth();
    size = my_texture.GetWidth();

    currentFrame = 0;
}

void Animation::advanceFrame() {
    this->currentFrame += 1;
    this->currentFrame = this->currentFrame % this->numFrames;
}

void Animation::update_by_angle(float aim_angle) {
    float angle_per_frame = 180.0f / numFrames;

    float offset = 90;

    // En el sprite el gusano empieza apuntando hacia abajo, asi que le sumo el offset
    float angle_in_degrees = aim_angle * (180.0f / M_PI) + offset;

    int frame_index = angle_in_degrees / angle_per_frame;

    // El # de frames es numFrames, pero los indices son de [0, numFrames - 1]. 
    frame_index = std::min(numFrames - 1, frame_index);

    currentFrame = frame_index;
}
