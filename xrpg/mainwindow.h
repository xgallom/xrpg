#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    MainWindow(QWindow *parent = nullptr);

protected:
    void initializeGL() final;
    void paintGL() final;
    void resizeGL(int width, int height) final;

protected slots:
    void on_timer_timeout();

private:
    QRect m_boundingRect;
    QPointF m_gradientOffset;
};
#endif // MAINWINDOW_H
