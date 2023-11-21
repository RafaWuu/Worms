/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../configuration/configuration.h"

#include "texture_controller.h"

#define FRAME_RATE (1.0 / Configuration::get_instance().get_fps())

class SdlTexture;
class Area;

class Animation {
public:
    Animation(std::shared_ptr<SDL2pp::Texture> texture, TextureController& controller);
    ~Animation();
    void update(float dt);
    void render(SDL2pp::Renderer& renderer, const SDL2pp::Rect dest, SDL_RendererFlip& flipType);
    void change_texture(AnimationState new_state);

private:
    void advanceFrame();
    /** SDL texture of the raw image. */
    std::shared_ptr<SDL2pp::Texture> texture;
    /** Current animation frame. */
    int currentFrame;
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Size of the sprite (height and width). */
    int size;
    /** Time elapsed since last update. */
    float elapsed;

    AnimationState state;

    TextureController& texture_controller;
};

#endif  //__ANIMATION_H__
