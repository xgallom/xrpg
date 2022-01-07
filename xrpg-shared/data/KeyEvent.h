#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QString>

struct KeyEvent {
    enum Type {
        Type_Press = 0,
        Type_PressAutoRepeat,
        Type_Release,
        Type_ReleaseAutoRepeat,
    };
    Type type;
    int key;
    QString text;
};

#endif // KEYEVENT_H
