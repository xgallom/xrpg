#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <QSize>
#include <QVector>
#include <QColor>
#include <QDataStream>

struct LevelData
{
    LevelData(QSize dimensions = QSize());
    void resize(QSize newDimensions);

    size_t width() const;
    size_t height() const;

    uint8_t *row(size_t y);
    const uint8_t *row(size_t y) const;

    QSize dimensions;
    QVector<uint8_t> symbols;
    QVector<QColor> colors;
};

QDataStream &operator<<(QDataStream &stream, const LevelData &item);
QDataStream &operator>>(QDataStream &stream, LevelData &item);

#endif // LEVELDATA_H
