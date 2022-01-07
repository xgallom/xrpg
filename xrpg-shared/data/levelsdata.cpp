#include "levelsdata.h"

LevelsData::LevelsData(size_t size) :
    levels(size)
{}

QDataStream &operator<<(QDataStream &stream, const LevelsData &item)
{
    return stream << item.levels;
}

QDataStream &operator>>(QDataStream &stream, LevelsData &item)
{
    return stream >> item.levels;
}
