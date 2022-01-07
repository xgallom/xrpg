#include "engine.h"
#include "engineworker.h"

Engine::Engine(EngineWorker *worker)
    : m_worker(worker)
{
    m_worker->moveToThread(&m_workerThread);
}

void Engine::start()
{
    m_workerThread.start();

    QMetaObject::invokeMethod(
                m_worker,
                "start",
                Qt::BlockingQueuedConnection
                );
}

Engine::~Engine()
{
    m_workerThread.quit();
    m_workerThread.wait();
}
