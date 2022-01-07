#include "leveldata.h"

LevelData::LevelData(QSize dimensions) :
    dimensions(dimensions),
    symbols(dimensions.width() * dimensions.height()),
    colors(dimensions.width() * dimensions.height())
{}

void LevelData::resize(QSize newDimensions)
{
    dimensions = newDimensions;
    symbols.resize(dimensions.width() * dimensions.height());
    colors.resize(dimensions.width() * dimensions.height());
}

size_t LevelData::width() const
{
    return dimensions.width();
}

size_t LevelData::height() const
{
    return dimensions.height();
}

uint8_t *LevelData::row(size_t y)
{
    return symbols.begin() + (y * width());
}

const uint8_t *LevelData::row(size_t y) const
{
    return symbols.cbegin() + (y * width());
}

QDataStream &operator<<(QDataStream &stream, const LevelData &item)
{
    return stream << item.dimensions << item.symbols << item.colors;
}

QDataStream &operator>>(QDataStream &stream, LevelData &item)
{
    return stream >> item.dimensions >> item.symbols >> item.colors;
}
