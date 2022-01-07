QT += gui opengl \
    widgets

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data/leveldata.cpp \
    data/levelsdata.cpp \
    system/engine.cpp \
    system/engineworker.cpp \
    system/mainwindow.cpp

HEADERS += \
    data/KeyEvent.h \
    data/leveldata.h \
    data/levelsdata.h \
    system/engine.h \
    system/engineworker.h \
    system/mainwindow.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
