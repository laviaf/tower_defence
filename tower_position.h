#ifndef TOWER_POSITION_H
#define TOWER_POSITION_H

#include "func_button.h"
#include "tower.h"

#include <QPoint>
#include <QPixmap>
#include <QString>
//这是塔基类

class func_button;
class tower;

class tower_position
{
public:
    tower_position(QPoint _pos);
    void draw(QPainter *painter);
    //绘制塔基
    bool has_tower_pos(QPoint p);
    //判断p处有无塔基
    bool has_tower();
    //判断此处塔基有无防御塔建立
    void set_has_tow();
    //塔基处建塔
    void removed_tow();
    //塔基处拆塔
    QPoint get_pos();
    //获取塔基位置
    void set_tower(tower* t);
    //保存此塔基处塔的位置
    func_button* get_fun_btn();
    bool has_fun_btn();
    void set_fun_btn(func_button *btn);
    tower* get_tower_info();
private:
    QPoint tow_pos;
    QPixmap tow_image;
    bool has_tow;

    func_button *fun_btn;
    tower* tow;
};

#endif // TOWER_POSITION_H
