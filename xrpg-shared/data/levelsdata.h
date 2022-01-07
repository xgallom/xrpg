#ifndef LEVELSDATA_H
#define LEVELSDATA_H

#include "leveldata.h"

struct LevelsData
{
    LevelsData(size_t size = 0);

    QVector<LevelData> levels;
};

QDataStream &operator<<(QDataStream &stream, const LevelsData &item);
QDataStream &operator>>(QDataStream &stream, LevelsData &item);

#endif // LEVELSDATA_H
