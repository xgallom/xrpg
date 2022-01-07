#include "xrpgengineworker.h"
#include <QDebug>

XRpgEngineWorker::XRpgEngineWorker()
{
    setStartHandler(&XRpgEngineWorker::startHandler);
    setTickHandler(&XRpgEngineWorker::tickHandler);
}

void XRpgEngineWorker::startHandler()
{
}

void XRpgEngineWorker::tickHandler()
{
    while (!m_keyEvents->isEmpty()) {
        const auto keyEvent = m_keyEvents->dequeue();
        qDebug() << keyEvent.type << keyEvent.key << keyEvent.text;
    }
}
