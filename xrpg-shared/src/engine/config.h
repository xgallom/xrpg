//
// Created by gallo on 24-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_SRC_ENGINE_CONFIG_H
#define XRPG_XRPG_SHARED_SRC_ENGINE_CONFIG_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

namespace engine::Config {
    constexpr uint32_t
            SDLFlags = SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO,
            ImgFlags = IMG_INIT_PNG,
            MixFlags = MIX_INIT_MP3,
            PixelFormat = SDL_PIXELFORMAT_XBGR8888,
            PixelDepth = 32;
}

#endif //XRPG_XRPG_SHARED_SRC_ENGINE_CONFIG_H
