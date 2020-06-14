#include "tower_position.h"
#include <QPainter>
#include <QPixmap>
#include <iostream>
using namespace std;

tower_position::tower_position(QPoint _pos):tow_pos(_pos),has_tow(false){
    tow_image.load(":/material/tower_set.png");
}

//�ж�һ���㴦��������
bool tower_position::has_tower_pos(QPoint p){
    bool has_x=tow_pos.x()<p.x()&&p.x()<tow_pos.x()+tow_image.width()/2;
    bool has_y=tow_pos.y()<p.y()&&p.y()<tow_pos.y()+tow_image.height()/2;
    return has_x&&has_y;
}

//�жϴ˴��������޷���������
bool tower_position::has_tower(){
    return this->has_tow;
}

void tower_position::set_tow(QPainter *painter){
    painter->drawPixmap(tow_pos.x(),tow_pos.y(),tow_image.width(),tow_image.height(),tow_image);
}

void tower_position::set_has_tow(){
    this->has_tow=true;
}

//��ȡ����λ��
QPoint tower_position::get_pos(){
    return this->tow_pos;
}
