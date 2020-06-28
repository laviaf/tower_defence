#ifndef BULLET_H
#define BULLET_H

#include "enemy.h"
#include "level1.h"

#include <QPoint>
#include <QImage>
#include <QPropertyAnimation>
#include <QPainter>
#include <QObject>

class level1;
class enemy;

class bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint cur_pos READ current_pos WRITE set_current_pos)
public:
    explicit bullet(QPoint start_P,QPoint target_P,int dam,enemy *ene,level1 *game);
    void move();
    void draw(QPainter *painter);
    QPoint current_pos();
    void set_current_pos(QPoint p);
private slots:
    void hit_target();
private:
    QPoint start_pos;
    QPoint target_pos;
    QPoint cur_pos;
    int damage;
    enemy *target;
    QImage bul_img;
    level1 *game_1;
signals:

public slots:
};

#endif // BULLET_H
