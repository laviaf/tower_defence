#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QImage>
#include <QPainter>

class tower
{
public:
    tower(QPoint pos, int t_num);
    void draw(QPainter *painter);
private:
    int fire_rate;
    int attack_range;
    int damage;
    QPoint t_pos;
    QImage t_img;
};

#endif // TOWER_H
