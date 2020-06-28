#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QImage>

class win_window : public QMainWindow
{
    Q_OBJECT
public:
    explicit win_window(QWidget *parent = nullptr);
    void draw(QPainter *painter);
signals:

public slots:
private:
    QImage img;
};

#endif // WIN_WINDOW_H
