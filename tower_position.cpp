#include "tower_position.h"
#include <QPainter>
#include <QPixmap>
#include <iostream>
using namespace std;

tower_position::tower_position(QPoint _pos):tow_pos(_pos),has_tow(false){
    tow_image.load(":/material/tower_set.png");
}

bool tower_position::has_tower(QPoint p){
    bool has_x=tow_pos.x()<p.x()&&p.x()<tow_pos.x()+tow_image.width()/2;
    bool has_y=tow_pos.y()<p.y()&&p.y()<tow_pos.y()+tow_image.height()/2;
    return has_x&&has_y;
}
//判断一个点处有无塔基

void tower_position::set_tow(QPainter *painter){
    painter->drawPixmap(tow_pos.x(),tow_pos.y(),tow_image.width(),tow_image.height(),tow_image);
}
