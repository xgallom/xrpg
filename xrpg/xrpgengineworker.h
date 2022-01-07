#ifndef XRPGENGINEWORKER_H
#define XRPGENGINEWORKER_H

#include <system/engineworker.h>

class XRpgEngineWorker : public EngineWorker
{
    Q_OBJECT
public:
    XRpgEngineWorker();

private:
    void startHandler();
    void tickHandler();
};

#endif // XRPGENGINEWORKER_H
