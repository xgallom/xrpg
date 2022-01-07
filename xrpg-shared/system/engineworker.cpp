#include "engineworker.h"
#include "mainwindow.h"
#include <QDebug>

static const int TickInterval = 1000 / 30;

void EngineWorker::attach(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;
}

void EngineWorker::keyEvent(const KeyEvent &event)
{
    m_keyEvents->enqueue(event);
}

void EngineWorker::start()
{
    m_tickTimer = new QTimer(this);
    m_tickTimer->setTimerType(Qt::PreciseTimer);

    m_elapsedTimer.reset(new QElapsedTimer());
    m_keyEvents.reset(new QQueue<KeyEvent>());

    connect(m_tickTimer, &QTimer::timeout, this, m_tickHandler);
    connect(m_mainWindow, &MainWindow::keyReceived, this, &EngineWorker::keyEvent);

    (this->*m_startHandler)();

    m_tickTimer->start(TickInterval);
    m_elapsedTimer->start();
}
