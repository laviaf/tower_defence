#ifndef LEVEL1_H
#define LEVEL1_H

#include "enemy.h"

#include <QMainWindow>
#include <QList>

class level1 : public QMainWindow
{
    Q_OBJECT
public:
    explicit level1(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void get_enemy(QList<QPoint*> ene_way);
    void updateScene();
signals:

public slots:
private:
    QList<enemy*> enemy_list;
};

#endif // LEVEL1_H
