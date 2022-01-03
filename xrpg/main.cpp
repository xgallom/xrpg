#include "mainwindow.h"

#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(true);

    MainWindow w;
    w.resize(900, 800);
    w.show();
//    w.showFullScreen();

    return a.exec();
}
