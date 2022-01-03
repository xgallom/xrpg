QT       += core gui opengl

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../xrpg-shared/release/ -lxrpg-shared
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../xrpg-shared/debug/ -lxrpg-shared
else:unix: LIBS += -L$$OUT_PWD/../xrpg-shared/ -lxrpg-shared

INCLUDEPATH += $$PWD/../xrpg-shared
DEPENDPATH += $$PWD/../xrpg-shared

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xrpg-shared/release/libxrpg-shared.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xrpg-shared/debug/libxrpg-shared.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xrpg-shared/release/xrpg-shared.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../xrpg-shared/debug/xrpg-shared.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../xrpg-shared/libxrpg-shared.a
