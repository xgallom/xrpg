//
// Created by gallo on 24-Jan-22.
//

#include <map/map.h>

namespace map {
    void StaticData::resize(size_t newSize)
    {
        symbols.resize(newSize);
        colors.resize(newSize);
    }
}

size_t Map::size() const
{
    return width * height;
}

void Map::resize(uint32_t newWidth, uint32_t newHeight)
{
    width = newWidth;
    height = newHeight;

    staticData.resize(size());
}

