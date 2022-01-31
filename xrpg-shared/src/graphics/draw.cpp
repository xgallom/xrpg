//
// Created by gallo on 25-Jan-22.
//

#include <graphics/draw.h>

namespace graphics {
    void drawSymbols(
            SDL_Surface *output,
            SDL_Surface *font,
            const int *x,
            const int *y,
            const uint8_t *symbols,
            size_t count)
    {
        do {
            const auto symbol = *symbols++;

            SDL_Rect
                    src{symbol % 16, symbol / 16, 16, 16},
                    dest{*x++ * 16, *y++ * 16, 16, 16};

            SDL_BlitSurface(font, &src, output, &dest);
        } while (--count);
    }

}
