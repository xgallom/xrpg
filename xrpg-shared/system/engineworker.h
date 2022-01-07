#ifndef ENGINEWORKER_H
#define ENGINEWORKER_H

#include <QObject>
#include <data/KeyEvent.h>
#include <QTimer>
#include <QQueue>
#include <QElapsedTimer>

class MainWindow;

class EngineWorker : public QObject
{
    Q_OBJECT
public:
    using StartHandler = void (EngineWorker::*)();
    using TickHandler = void (EngineWorker::*)();

    void attach(MainWindow *mainWindow);

public slots:
    void keyEvent(const KeyEvent &event);
    void start();

protected:
    template<typename T>
    inline void setStartHandler(void (T::*startHandler)())
    {
        m_startHandler = reinterpret_cast<StartHandler>(startHandler);
    }

    template<typename T>
    inline void setTickHandler(void (T::*tickHandler)())
    {
        m_tickHandler = reinterpret_cast<TickHandler>(tickHandler);
    }

    MainWindow *m_mainWindow;
    QTimer *m_tickTimer;
    QScopedPointer<QElapsedTimer> m_elapsedTimer;
    QScopedPointer<QQueue<KeyEvent>> m_keyEvents;

private:
    StartHandler m_startHandler;
    TickHandler m_tickHandler;
};

#endif // ENGINEWORKER_H
