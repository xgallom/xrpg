#include "mainwindow.h"
#include <QPainter>
#include <QRect>
#include <cmath>
#include <QTimer>
#include <QDebug>

static const double AspectRatio = 16.0 / 9.0;
//static const double AspectRatio = 1;
static const int CharWidth = 32, CharHeight = 32;

static const uint8_t Map[16][16] = {
    {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0xd5, 0xc4, 0xc4, 0xc4, 0xb7, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0xb3, 0x00, 0x00, 0x00, 0xb3, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0xb3, 0x00, 0x24, 0x00, 0xb3, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0xb3, 0x00, 0x00, 0x00, 0xb3, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0xb3, 0x00, 0x00, 0x00, 0xb3, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0xb3, 0x00, 0x00, 0x00, 0xb3, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0xc0, 0xc4, 0xc4, 0xc4, 0xbc, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
    {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20},
};

MainWindow::MainWindow(QWindow *parent)
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate, parent)
{}

void MainWindow::initializeGL()
{}

void MainWindow::paintGL()
{
    QPainter painter;
    QColor fill(255, 147, 41);

    QPixmap glyphs("./assets/img/glyphs.png");

    auto &toDraw = glyphs;

    QRadialGradient gradient(0, 0, 0.5);
    gradient.setCoordinateMode(QGradient::ObjectMode);
    gradient.setColorAt(0, fill.darker(100 * 0.75));
    gradient.setColorAt(0.1, fill.darker(100));
    gradient.setColorAt(0.2, fill.darker(100 * 4));
    gradient.setColorAt(0.3, fill.darker(100 * 9));
    gradient.setColorAt(0.4, fill.darker(100 * 16));
    gradient.setColorAt(0.5, fill.darker(100 * 25));
    gradient.setColorAt(0.6, fill.darker(100 * 36));
    gradient.setColorAt(0.7, fill.darker(100 * 49));
    gradient.setColorAt(0.8, fill.darker(100 * 64));
    gradient.setColorAt(0.9, fill.darker(100 * 81));
    gradient.setColorAt(1, QColor(Qt::black));

    painter.begin(this);
    painter.fillRect(QRect(QPoint(), size()), fill);
    painter.fillRect(m_boundingRect, Qt::black);

    for (auto y = 0; y < 16; ++y) {
        for (auto x = 0; x < 16; ++x) {
            const auto offset = Map[y][x];

            painter.drawPixmap(
                        QRect(
                            m_boundingRect.topLeft() + QPoint(x * CharWidth, y * CharHeight),
                            QSize(CharWidth, CharHeight)
                            ),
                        toDraw,
                        QRect(
                            CharWidth * (offset % 16),
                            CharHeight * (offset / 16),
                            CharWidth,
                            CharHeight
                            )
                        );
        }
    }

    painter.setCompositionMode(QPainter::CompositionMode_Overlay);
    painter.setBrush(QBrush(QColor(0, 200, 0)));
    painter.drawRect(QRect(m_boundingRect.topLeft() + QPoint(2 * CharWidth, 3 * CharHeight), QSize(CharWidth, CharHeight)));
    painter.setCompositionMode(QPainter::CompositionMode_HardLight);
//    painter.drawPixmap(m_boundingRect.topLeft(), other);
//    painter.setBrush(QBrush(gradient));
//    painter.drawRect(m_boundingRect);
    painter.end();
}

void MainWindow::resizeGL(int width, int height)
{
    if (!width || !height)
        m_boundingRect = QRect();
    else {
        // Floor number of characters fitting on screen
        const auto
                charsX = (width / CharWidth) * CharWidth,
                charsY = (height / CharHeight) * CharHeight;

        // Align to correct aspect ratio
        const auto viewAspectRatio = double(charsX) / double(charsY);
        int contentWidth, contentHeight;

        if (AspectRatio < viewAspectRatio) {
            contentWidth = round(charsY * AspectRatio);
            contentHeight = charsY;
        } else {
            contentWidth = charsX;
            contentHeight = round(charsX / AspectRatio);
        }

        // Center content
        m_boundingRect = QRect(
                    (width - contentWidth) / 2,
                    (height - contentHeight) / 2,
                    contentWidth,
                    contentHeight
                    );
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    emit keyReceived(KeyEvent{
                         .type = event->isAutoRepeat() ? KeyEvent::Type_PressAutoRepeat : KeyEvent::Type_Press,
                         .key = event->key(),
                         .text = event->text(),
                     });

    QOpenGLWindow::keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    emit keyReceived(KeyEvent{
                         .type = event->isAutoRepeat() ? KeyEvent::Type_ReleaseAutoRepeat : KeyEvent::Type_Release,
                         .key = event->key(),
                         .text = event->text(),
                     });

    QOpenGLWindow::keyReleaseEvent(event);
}
