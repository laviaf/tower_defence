#include "tower_position.h"
#include <QPainter>
#include <QPixmap>
#include <iostream>
using namespace std;

tower_position::tower_position(QPoint _pos):tow_pos(_pos),has_tow(false),fun_btn(NULL),tow(NULL)
{
    tow_image.load(":/material/tower_set.png");
}

//判断一个点处有无塔基
bool tower_position::has_tower_pos(QPoint p){
    bool has_x=tow_pos.x()<p.x()&&p.x()<tow_pos.x()+tow_image.width();
    bool has_y=tow_pos.y()<p.y()&&p.y()<tow_pos.y()+tow_image.height();
    return has_x&&has_y;
}

//判断此处塔基有无防御塔建立
bool tower_position::has_tower(){
    return this->has_tow;
}

void tower_position::draw(QPainter *painter){
    painter->drawPixmap(tow_pos.x(),tow_pos.y(),tow_image.width(),tow_image.height(),tow_image);
}

void tower_position::set_has_tow(){
    this->has_tow=true;
}

void tower_position::removed_tow(){
    has_tow=false;
}

//获取塔基位置
QPoint tower_position::get_pos(){
    return this->tow_pos;
}

void tower_position::set_fun_btn(func_button *btn){
    fun_btn=btn;
}

func_button* tower_position::get_fun_btn(){
    return fun_btn;
}

void tower_position::set_tower(tower *t){
    tow=t;
}

tower* tower_position::get_tower_info(){
    return tow;
}

bool tower_position::has_fun_btn(){
    if(fun_btn==NULL)
        return false;
    else
        return true;
}
