#include "mainwindow.h"
#include "enemy.h"

#include <QList>
#include <QApplication>
#include <QPoint>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
