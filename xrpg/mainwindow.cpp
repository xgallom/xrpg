#include "mainwindow.h"
#include <QPainter>
#include <QRect>
#include <cmath>
#include <QTimer>
#include <QDebug>

//static const double AspectRatio = 16.0 / 9.0;
static const double AspectRatio = 1;
static const int CharWidth = 16, CharHeight = 16;

MainWindow::MainWindow(QWindow *parent)
    : QOpenGLWindow(QOpenGLWindow::NoPartialUpdate, parent)
{}

void MainWindow::on_timer_timeout()
{
    m_gradientOffset += QPointF(0.005, 0.005);
    requestUpdate();
}

void MainWindow::initializeGL()
{
    auto *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::on_timer_timeout);
    timer->start(1000 / 30);
}

void MainWindow::paintGL()
{
    QPainter painter;
    QColor fill(255, 147, 41);

    QPixmap glyphs("./assets/img/glyphs.png");

    auto &toDraw = glyphs;

    QRadialGradient gradient(m_gradientOffset, 0.2);
    gradient.setCoordinateMode(QGradient::ObjectMode);
    gradient.setColorAt(0, fill);
    gradient.setColorAt(0.1, fill.darker(100 * 2));
    gradient.setColorAt(0.2, fill.darker(100 * 4));
    gradient.setColorAt(0.3, fill.darker(100 * 8));
    gradient.setColorAt(0.4, fill.darker(100 * 16));
    gradient.setColorAt(0.5, fill.darker(100 * 32));
    gradient.setColorAt(0.6, fill.darker(100 * 64));
    gradient.setColorAt(0.7, fill.darker(100 * 128));
    gradient.setColorAt(0.8, fill.darker(100 * 256));
    gradient.setColorAt(0.9, fill.darker(100 * 512));
    gradient.setColorAt(1, QColor(Qt::black));
    const auto c = fill.darker(100 * 4);
    qDebug() << c.red() << c.green() << c.blue();

    painter.begin(this);
    painter.fillRect(QRect(QPoint(), size()), fill);
    painter.fillRect(m_boundingRect, Qt::black);

    for (auto y = 0; y < 4; ++y) {
        for (auto x = 0; x < 4; ++x) {
            painter.drawPixmap(
                        QRect(
                            m_boundingRect.topLeft() + QPoint(x * m_boundingRect.width() / 4, y * m_boundingRect.height() / 4),
                            QSize(m_boundingRect.width() / 4, m_boundingRect.height() / 4)
                            ),
                        toDraw
                        );
        }
    }

    painter.setCompositionMode(QPainter::CompositionMode_HardLight);
//    painter.drawPixmap(m_boundingRect.topLeft(), other);
    painter.setBrush(QBrush(gradient));
    painter.drawRect(m_boundingRect);
    painter.end();
}

void MainWindow::resizeGL(int width, int height)
{
    if (!width || !height)
        m_boundingRect = QRect();
    else {
        const auto
                charsX = (width / CharWidth) * CharWidth,
                charsY = (height / CharHeight) * CharHeight;

        const auto viewAspectRatio = double(charsX) / double(charsY);
        int contentWidth, contentHeight;

        if (AspectRatio < viewAspectRatio) {
            contentWidth = round(charsY * AspectRatio);
            contentHeight = charsY;
        } else {
            contentWidth = charsX;
            contentHeight = round(charsX / AspectRatio);
        }

        m_boundingRect = QRect(
                    (width - contentWidth) / 2,
                    (height - contentHeight) / 2,
                    contentWidth,
                    contentHeight
                    );
    }
}
