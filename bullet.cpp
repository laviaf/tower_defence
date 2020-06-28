#include "bullet.h"

#include <iostream>
using namespace std;

bullet::bullet(QPoint start_P, QPoint target_P, int dam, enemy *ene, level1 *game):
    start_pos(start_P),target_pos(target_P),cur_pos(start_P),damage(dam),target(ene),game_1(game)
{
    this->bul_img.load(":/tower/material/bullet.png");
}

void bullet::draw(QPainter *painter){
    painter->drawImage(cur_pos,bul_img);
}

void bullet::move(){
    //�趨0.1�붯��
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "cur_pos");
    animation->setDuration(duration);
    animation->setStartValue(start_pos);
    animation->setEndValue(target_pos);
    connect(animation, SIGNAL(finished()), this, SLOT(hit_target()));

    animation->start();
}

void bullet::hit_target(){
    //�жϵ����Ƿ����
    if(this->game_1->get_ene_list().indexOf(target)!=-1)
        target->get_damaged(damage);
    //������� �ӵ���ʧ
    game_1->remove_bullet(this);
}

QPoint bullet::current_pos(){
    return this->cur_pos;
}

void bullet::set_current_pos(QPoint p){
    this->cur_pos=p;
}
