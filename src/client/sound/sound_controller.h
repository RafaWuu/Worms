#ifndef _SOUND_CONTROLLER_H_
#define _SOUND_CONTROLLER_H_

#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLMixer.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>
#include <SDL2pp/Chunk.hh>

class SoundController {

private:
    SDL2pp::Mixer& mixer;

public:
    SoundController(SDL2pp::Mixer& mixer);

    void set_background_music();
};

#endif