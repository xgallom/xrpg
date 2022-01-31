//
// Created by gallo on 25-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_GRAPHICS_COLOR_PALETTE_H
#define XRPG_XRPG_SHARED_INCLUDE_GRAPHICS_COLOR_PALETTE_H

#include <cstdint>

namespace graphics {
    extern const uint32_t ColorPalette[256];
    extern uint32_t RowColorPalette[256][16];

    void initColorPalette();
}

#endif //XRPG_XRPG_SHARED_INCLUDE_GRAPHICS_COLOR_PALETTE_H
