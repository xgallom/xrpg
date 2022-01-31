//
// Created by gallo on 24-Jan-22.
//

#include <engine/audio.h>
#include "config.h"

namespace engine {
    bool Audio::init()
    {
        const auto initFlags = uint32_t(Mix_Init(Config::MixFlags));
        if ((initFlags & Config::MixFlags) != Config::MixFlags)
            return false;

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024))
            return false;

        return true;
    }

    void Audio::deinit()
    {
        Mix_CloseAudio();
        Mix_Quit();
    }
}
