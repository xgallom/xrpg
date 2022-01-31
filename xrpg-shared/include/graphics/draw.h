//
// Created by gallo on 25-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_GRAPHICS_DRAW_H
#define XRPG_XRPG_SHARED_INCLUDE_GRAPHICS_DRAW_H

#include <cstdint>
#include <SDL_surface.h>

namespace graphics {
    void drawSymbols(
            SDL_Surface *output,
            const SDL_Surface *font,
            const uint32_t *x,
            const uint32_t *y,
            const uint8_t *symbols,
            size_t count
    );
}

#endif //XRPG_XRPG_SHARED_INCLUDE_GRAPHICS_DRAW_H
