//
// Created by gallo on 24-Jan-22.
//

#ifndef XRPG_XRPG_SHARED_INCLUDE_MAP_MAP_H
#define XRPG_XRPG_SHARED_INCLUDE_MAP_MAP_H

#include <vector>
#include <cstdint>
#include <SDL_pixels.h>

namespace map {
    using Symbol = uint8_t;
    using Color = uint32_t;

    struct StaticData {
        std::vector<Symbol> symbols;
        std::vector<Color> colors;

        void resize(size_t newSize);
    };
}

struct Map {
    uint32_t width, height;
    map::StaticData staticData;

    [[nodiscard]]
    size_t size() const;
    void resize(uint32_t newWidth, uint32_t newHeight);
};

#endif //XRPG_XRPG_SHARED_INCLUDE_MAP_MAP_H
