#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QVector2D>
#include <QPainter>
#include <QImage>
#include <QPoint>
#include <QString>
#include <QList>

#include "level1.h"
#include "tower.h"
#include "way_point.h"
//敌人行走所需航点

class tower;
class level1;

class enemy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint enemy_pos_current READ getpos WRITE set_cur_pos)
public:
    explicit enemy(way_point *start_point, int _num, level1 *game_1);
    QPoint getpos();
    void set_cur_pos(QPoint p);
    void draw(QPainter *painter);
    void move();
    void get_removed();
    void get_damaged(int dam_hp);
    ~enemy();
    //未实现函数
    void ene_de_blood();//减少血量
    void add_tower_attacked(tower *tow);
    void get_lose_sight(tower *tow);
signals:

public slots:
    void doActivate();
private:
    way_point* enemy_dest_point;//敌人向此点行进
    QPoint enemy_pos_current;//敌人当前位置
    QImage enemy_img;
    qreal walk_speed;
    bool is_active;
    int Hp_max;
    int Hp_current;
    int num;//用于切换不同关卡怪物
    QList<tower*> tower_attacked_list;//记录被攻击的塔，以防被两座塔同时delete
    level1* game;

    int die_num;
};

#endif // ENEMY_H
