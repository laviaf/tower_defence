#ifndef LEVEL1_H
#define LEVEL1_H

#include "way_point.h"
#include "enemy.h"
#include "tower_position.h"
#include "tower.h"

#include <QMainWindow>
#include <QList>

class level1 : public QMainWindow
{
    Q_OBJECT
public:
    explicit level1(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    //构造敌人波次
    void loadwave(int ene_num);
    //获得一个敌人
    void get_enemy(QList<way_point *> route);
    void updateScene();
    //设定第一关路线
    void set_route();
    //鼠标事件
    void mousePressEvent(QMouseEvent *event);
    bool can_buy_tower();
signals:

public slots:

private:
    QList<tower_position*> tow_base_list;
    //塔基位置
    QList<enemy*> enemy_list;
    int base_Hp;
    QList<way_point*> route;
    //敌人航线
    QList<tower*> tower_list;
    int money;
};

#endif // LEVEL1_H
