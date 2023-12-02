#include "sound_controller.h"

SoundController::SoundController(SDL2pp::Mixer& mixer) : mixer(mixer), background_channel(0), sound_effect_channel(1) {
    std::map<Sound, std::string> sounds_to_load = {
        {CURSOR_SELECT, "CursorSelect.wav"},
        {BACKGROUND_MUSIC, "background_music.mp3"},
        {JUMP, "JUMP1.WAV"},
        {WALK, "Walk.wav"},
        {THROW, "Throw.wav"},
        {EXPLOSION, "Explosion1.wav"},
        {DEATH, "BYEBYE.WAV"}
    };

    for (auto& [sound, file_name] : sounds_to_load) {
        load_sound(sound, file_name);
    }
    
    mixer.SetVolume(background_channel, Configuration::get_instance().get_bg_music_volume());
    mixer.SetVolume(sound_effect_channel, Configuration::get_instance().get_sound_effect_volume());
}

void SoundController::set_background_music() {
    std::shared_ptr<SDL2pp::Chunk> bg_music = sounds[BACKGROUND_MUSIC];

    mixer.PlayChannel(background_channel, *bg_music, -1);     
}

void SoundController::load_sound(Sound sound, std::string file_name) {
    std::string path("../assets/sounds/" + file_name);
    std::string alternative_path("assets/sounds/" + file_name);

    try {

        auto sound_effect = std::make_shared<SDL2pp::Chunk> (path);
        sounds.emplace(sound, sound_effect);

    } catch (SDL2pp::Exception& e) {

        auto sound_effect = std::make_shared<SDL2pp::Chunk> (alternative_path);
        sounds.emplace(sound, sound_effect);

    }   
}

void SoundController::play_sound(Sound sound) {
    // Para que no spamee el sonido al caminar. Hardcodeado?
    if (sound == WALK && mixer.IsChannelPlaying(sound_effect_channel)) {
        return;
    }

    std::shared_ptr<SDL2pp::Chunk> sound_effect = sounds[sound];

    mixer.PlayChannel(sound_effect_channel, *sound_effect, 0);
}

void SoundController::stop_sound() {
    mixer.HaltChannel(sound_effect_channel);
}


