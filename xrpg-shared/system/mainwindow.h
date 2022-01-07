#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>
#include <QKeyEvent>
#include <data/KeyEvent.h>

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    MainWindow(QWindow *parent = nullptr);

signals:
    void keyReceived(const KeyEvent &event);

protected:
    void initializeGL() final;
    void paintGL() final;
    void resizeGL(int width, int height) final;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    QRect m_boundingRect;
};
#endif // MAINWINDOW_H
