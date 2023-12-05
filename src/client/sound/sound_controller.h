#ifndef _SOUND_CONTROLLER_H_
#define _SOUND_CONTROLLER_H_

#include <map>
#include <memory>
#include <string>

#include <SDL2pp/Chunk.hh>
#include <SDL2pp/Mixer.hh>
#include <SDL2pp/Music.hh>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/SDLMixer.hh>

#include "../../../configuration/configuration.h"

enum Sound {
    BACKGROUND_MUSIC,
    CURSOR_SELECT,
    JUMP,
    WALK,
    THROW,
    EXPLOSION,
    DEATH,
};

class SoundController {

private:
    SDL2pp::Mixer& mixer;

    std::map<Sound, std::shared_ptr<SDL2pp::Chunk>> sounds;

    void load_sound(Sound, std::string file_name);

    int background_channel;
    int sound_effect_channel;

public:
    explicit SoundController(SDL2pp::Mixer& mixer);

    void set_background_music();

    void play_sound(Sound);

    void stop_sound();
};

#endif
