#include "sound_controller.h"

SoundController::SoundController(SDL2pp::Mixer& mixer) : mixer(mixer) {}

void SoundController::set_background_music() {
    mixer.SetMusicVolume(50);

    std::string path("../assets/sounds/background_music.mp3");
    std::string alternative_path("assets/sounds/background_music.mp3");

    try {

        SDL2pp::Music music(path);
        mixer.PlayMusic(music, -1);

    } catch (SDL2pp::Exception& e) {

        SDL2pp::Music music(alternative_path);
        mixer.PlayMusic(music, -1);
        
    }    
}