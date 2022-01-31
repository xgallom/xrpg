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
#include <SDL_image.h>

namespace run {
/*    void Start::update()
    {
        for (const auto &event : events.events) {
//            if (event.type == SDL_QUIT)
//                activeId = engine::EngineRunHandlerId::Quit;
        }
        events.events.clear();
    }

    void Start::render()
    {
        SDL_SetRenderDrawColor(renderer, 230, 120, 230, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        auto image = IMG_Load("assets/img/glyphs-16x16.png");
        if (!image) {
            printf("IMG_LoadPNG_RW: %s\n", IMG_GetError());
        } else {
            auto texture = SDL_CreateTextureFromSurface(renderer, image);
            SDL_FreeSurface(image);
            SDL_Rect src{64, 32, 32, 32}, dst{0, 0, 64, 64};
            SDL_RenderCopy(renderer, texture, &src, &dst);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);
    }*/
}
