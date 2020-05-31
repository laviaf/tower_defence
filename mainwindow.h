#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "world_map.h"
#include <QMainWindow>
#include <QPainter>
#include <Qpixmap>
#include <QPaintEvent>
#include <QPushButton>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void updateScene();
private:
    Ui::MainWindow *ui;
    world_map *map;
};

#endif // MAINWINDOW_H
