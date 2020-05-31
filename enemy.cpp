#include "enemy.h"

#include <QTimer>

enemy::enemy(QList<QPoint *> way, QString img) : QObject(0),enemy_img(img),enemy_way(way)
{
    enemy_pos=*way[0];
}

void enemy::draw(QPainter *painter){
    painter->drawPixmap(enemy_pos,enemy_img);
}

//仅为两点间运动
/*还没做沿路径运动*/
void enemy::move(){
    QPropertyAnimation *act = new QPropertyAnimation(this,"currentPos");
    act->setDuration(9000);
    act->setStartValue(*enemy_way[0]);
    int len=sizeof(enemy_way)/sizeof(enemy_way[0]);
    act->setEndValue(*enemy_way[len-1]);
    act->start();
}

QPoint enemy::get_ene_pos(){
    return this->enemy_pos;
}

void enemy::set_ene_pos(QPoint _pos){
    enemy_pos=_pos;
}
