// xrpg
// Copyright (C) 2022 Milan Gallo <gallo.milan.jr@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//
// Created by Milan Gallo on 19/01/2022.
//

#include <engine/init.h>
#include <SDL.h>

namespace engine {
    Init init()
    {
        Init init;
        auto &context = init.context;

        if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO))
            goto end;

        context.window = SDL_CreateWindow(
                "XRpg",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                800,
                600,
                SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALLOW_HIGHDPI
        );

        if (!context.window)
            goto end;

        context.renderer = SDL_CreateRenderer(
                context.window,
                -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );

        if (!context.renderer)
            goto end;

        SDL_RenderSetIntegerScale(context.renderer, SDL_TRUE);
        init.wasSuccessful = true;

        end:
        return init;
    }

    void deinit(const Context &context)
    {
        if (context.renderer)
            SDL_DestroyRenderer(context.renderer);
        if (context.window)
            SDL_DestroyWindow(context.window);

        SDL_Quit();
    }
}
