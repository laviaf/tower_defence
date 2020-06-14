#include "enemy.h"
#include "utility.h"

#include <QTimer>
#include <QVector>
#include <QPropertyAnimation>
#include <QMediaPlayer>

#include <iostream>
using namespace std;

enemy::enemy(QList<way_point*> route, int _num) : QObject(0),enemy_dest_point(route[1]),num(_num)
{
    switch (num) {
    case 1://新手村
    {
        enemy_img.load(":/enemy/material/enemy2(1).png");
        this->Hp_max=200;
        this->Hp_current=200;
        this->walk_speed=1.0;
        break;
    }
    case 2://人鱼村
    {
        QImage inst2;
        inst2.load(":/enemy/material/enemy1.png");
        enemy_img=inst2.copy(QRect(0,0,3,2));
        this->Hp_max=300;
        this->Hp_current=300;
        this->walk_speed=1.0;
        break;
    }
    default:
        break;
    }
    enemy_pos_current=route[0]->getpos();
}



void enemy::draw(QPainter *painter){
    //当前位置绘制敌人
    painter->drawImage(enemy_pos_current.x(),enemy_pos_current.y(),enemy_img);
    //保存painter状态
    painter->save();

    //绘制血条
    int Health_Bar_Width=enemy_img.width();
    QPoint Health_Bar_Point=enemy_pos_current+QPoint(0,-5);
    //设定血条位置
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect Health_Bar_Rect(Health_Bar_Point,QSize(Health_Bar_Width,2));
    painter->drawRect(Health_Bar_Rect);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::green);
    QRect Blood_remain_Rect(Health_Bar_Point,QSize(Health_Bar_Width*Hp_current/Hp_max,2));
    painter->drawRect(Blood_remain_Rect);

    painter->restore();
}


//敌人沿设定路径进行运动
//递归
void enemy::move(){
    utility judge;
    QPropertyAnimation *act = new QPropertyAnimation(this,"enemy_pos_current");
    act->setDuration(9000);
    act->setStartValue(enemy_pos_current);
    act->setEndValue(enemy_dest_point->getpos());
    act->start();
    if (judge.collisionRange(enemy_pos_current,1,enemy_dest_point->getpos(),1)){
        // 敌人抵达了一个航点
        if (enemy_dest_point->nextWayPoint())	{
            // 还有下一个航点
            enemy_pos_current=enemy_dest_point->getpos();
            enemy_dest_point=enemy_dest_point->nextWayPoint();
            move();
            return;
        }
        else
        {
            // 表示进入基地
            //留待实现基地血量减少及敌人判死函数
            return;
        }
    }
}

//若死亡，返回ture
bool enemy::is_dead(){
    if(this->Hp_current<0){
        return true;
    }
    else{
        return false;
    }
}

//用于获得敌人动画效果
QPoint enemy::get_ene_pos(){
    return this->enemy_pos_current;
}
void enemy::set_ene_pos(QPoint _pos){
    enemy_pos_current=_pos;
}

enemy::~enemy(){
    QMediaPlayer *ene_dead=new QMediaPlayer;
    ene_dead->setMedia(QUrl(":/music/material/enemy_dead.mp3"));
    ene_dead->setVolume(30);
    ene_dead->play();
}
