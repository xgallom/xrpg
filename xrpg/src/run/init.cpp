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
// Created by Milan Gallo on 20/01/2022.
//

#include "init.h"
#include <SDL.h>

namespace run {
    void start(engine::Context &context)
    {
        const auto renderer = context.renderer;
        SDL_SetRenderDrawColor(renderer, 255, 50, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                case SDL_KEYDOWN:
                case SDL_MOUSEBUTTONDOWN:
                    context.activeId = engine::EngineRunHandlerId::Quit;
            }
        }
    }

    void quit(engine::Context &) {}
}
