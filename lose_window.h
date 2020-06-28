#ifndef LOSE_WINDOW_H
#define LOSE_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QImage>

class lose_window : public QMainWindow
{
    Q_OBJECT
public:
    explicit lose_window(QWidget *parent = nullptr);
    void draw(QPainter *painter);
signals:

public slots:
private:
    QImage img;
};

#endif // LOSE_WINDOW_H
