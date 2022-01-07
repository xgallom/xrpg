#include <QGuiApplication>
#include <system/mainwindow.h>
#include <system/engine.h>
#include "xrpgengineworker.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);

    MainWindow mainWindow;

    EngineWorker *engineWorker = new XRpgEngineWorker();
    Engine engine(engineWorker);

    engineWorker->attach(&mainWindow);
    engine.start();

//    w.resize(900, 800);
//    w.show();
    mainWindow.showFullScreen();

    return a.exec();
}
