#ifndef TOWER_POSITION_H
#define TOWER_POSITION_H

#include <QPoint>
#include <QPixmap>
#include <QString>
class tower_position
{
public:
    tower_position(QPoint _pos);
    void set_tow(QPainter *painter);
    bool has_tower(QPoint p);
    //判断一个点处有无塔基
private:
    QPoint tow_pos;
    QPixmap tow_image;
    bool has_tow;
};

#endif // TOWER_POSITION_H
