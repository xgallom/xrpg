//
// Created by gallo on 23-Jan-22.
//

#include "engine/engine.h"
#include "config.h"

using namespace engine;

bool Engine::init()
{
    return !SDL_Init(Config::SDLFlags)
           && as<Audio>().init()
           && as<Renderer>().init()
           && as<Events>().init();
}

Engine::~Engine()
{
    as<Renderer>().deinit();
    as<Audio>().deinit();
    SDL_Quit();
}
