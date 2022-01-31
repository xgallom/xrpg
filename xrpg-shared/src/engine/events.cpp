//
// Created by gallo on 24-Jan-22.
//

#include <engine/events.h>

namespace engine {
    bool Events::init()
    {
        events.reserve(1024);
        SDL_PumpEvents();
        return true;
    }

    void Events::pollEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    events.push_back(e);
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    if (!e.key.repeat)
                        events.push_back(e);
                    break;
            }
        }
    }

}