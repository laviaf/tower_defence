#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QVector2D>
#include <QPainter>
#include <QImage>
#include <QPoint>
#include <QString>
#include <QList>

#include "way_point.h"
//敌人行走所需航点

class enemy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint enemy_pos_current READ get_ene_pos WRITE set_ene_pos)
public:
    explicit enemy(QList<way_point *> route, int _num);
    void draw(QPainter *painter);
    void move();
    QPoint get_ene_pos();
    void set_ene_pos(QPoint _pos);
    bool is_dead();//判断攻击塔攻击是否致死
    ~enemy();
    //未实现函数
    void ene_de_blood();//减少血量
signals:

public slots:
private:
    way_point* enemy_dest_point;//敌人向此点行进
    QPoint enemy_pos_current;//敌人当前位置
    QImage enemy_img;
    double walk_speed;
    int Hp_max;
    int Hp_current;
    int num;//用于切换不同关卡怪物

};

#endif // ENEMY_H
