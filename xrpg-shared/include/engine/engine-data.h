//
// Created by gallo on 24-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_ENGINE_ENGINE_DATA_H
#define XRPG_XRPG_SHARED_INCLUDE_ENGINE_ENGINE_DATA_H

#include <SDL_events.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <vector>

namespace engine {
    using Event = SDL_Event;

    struct EngineData {
        // Cache line
        SDL_Surface *font = nullptr;
        SDL_Renderer *renderer = nullptr;
        SDL_Surface *environment = nullptr;
        SDL_Surface *light = nullptr;
        SDL_Texture *output = nullptr;
        int screenW = 0, screenH = 0;
        uint64_t padding1, padding2;

        // Cache line
        std::vector<Event> events = {};
        SDL_Window *window = nullptr;

        template<typename As>
        constexpr As &as() { return static_cast<As &>(*this); }

        [[nodiscard]] inline int screenPxW() const { return screenW * 16; }
        [[nodiscard]] inline int screenPxH() const { return screenH * 16; }
    };
}

#endif //XRPG_XRPG_SHARED_INCLUDE_ENGINE_ENGINE_DATA_H
