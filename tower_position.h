#ifndef TOWER_POSITION_H
#define TOWER_POSITION_H

#include <QPoint>
#include <QPixmap>
#include <QString>
//这是塔基类
class tower_position
{
public:
    tower_position(QPoint _pos);
    void set_tow(QPainter *painter);
    //绘制塔基
    bool has_tower_pos(QPoint p);
    //判断p处有无塔基
    bool has_tower();
    //判断此处塔基有无防御塔建立
    void set_has_tow();
    //塔基处建塔
    QPoint get_pos();
    //获取塔基位置
private:
    QPoint tow_pos;
    QPixmap tow_image;
    bool has_tow;
};

#endif // TOWER_POSITION_H
