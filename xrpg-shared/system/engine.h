#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QThread>

class EngineWorker;

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(EngineWorker *worker);
    ~Engine();

    void start();

private:
    QThread m_workerThread;
    EngineWorker *m_worker;
};

#endif // ENGINE_H
