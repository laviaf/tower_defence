#include "tower.h"

#include <iostream>
using namespace std;

tower::tower(QPoint pos,int t_num):t_pos(pos)
{
    switch (t_num) {
    case 1://³õ¼¶Ëþ
    {
        t_img.load(":/tower/material/crew_lufu_1.png");
        this->fire_rate=2000;
        this->attack_range=100;
        this->damage=20;
        break;
    }
    case 2://¶þ¼¶Ëþ
    {
        QImage inst2;
        inst2.load(":/tower/material/crew_lufu_upgrade1.png");
        t_img=inst2.copy(QRect(2.5,1.9,2,2));
        this->fire_rate=1000;
        this->attack_range=170;
        this->damage=50;
        break;
    }
    default:
        break;
    }
}


void tower::draw(QPainter *painter){
    painter->save();

    //»­³ö¹¥»÷·¶Î§
    painter->setPen(Qt::red);
    painter->drawEllipse(t_pos,attack_range,attack_range);
    painter->drawImage(t_pos.x(),t_pos.y(),t_img);

    painter->restore();
}
