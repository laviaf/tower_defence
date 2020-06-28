#include "enemy.h"
#include "utility.h"

#include <QTimer>
#include <QVector>
#include <QMediaPlayer>
#include <QPropertyAnimation>
#include <QVector2D>

#include <iostream>
using namespace std;

enemy::enemy(way_point* start_point, int _num, level1* game_1) :
    QObject(0),enemy_dest_point(start_point->nextWayPoint()),num(_num),game(game_1),die_num(0)
{
    switch (num) {
    case 1://新手村 小兵1
    {
        enemy_img.load(":/enemy/material/enemy2(1).png");
        this->Hp_max=500;
        this->Hp_current=500;
        this->walk_speed=1.0;
        break;
    }
    case 2://新手村 小兵2
    {
        enemy_img.load(":/enemy/material/enemy1(1).png");
        this->Hp_max=300;
        this->Hp_current=300;
        this->walk_speed=5.0;
        break;
    }
    case 3://新手村 小兵3
    {
        enemy_img.load(":/enemy/material/enemy3(1).png");
        this->Hp_max=1800;
        this->Hp_current=1800;
        this->walk_speed=2.5;
        break;
    }
    case 4://新手村boss
    {
        enemy_img.load(":/enemy/material/baki.jpg");
        this->Hp_max=5000;
        this->Hp_current=5000;
        this->walk_speed=3.0;
        break;
    }
    default:
        break;
    }
    enemy_pos_current=start_point->getpos();
    is_active=false;
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
void enemy::move(){
    if(is_active==false){
        return;
    }

    utility judge;
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
            game->remove_enemy(this);
            game->damage_life();
            return;
        }
    }
    else{
        QPoint t_point = enemy_dest_point->getpos();
        double movementSpeed=walk_speed;
        QVector2D normalized(t_point-enemy_pos_current);
        normalized.normalize();
        enemy_pos_current = enemy_pos_current + normalized.toPoint()*movementSpeed;
    }
}

QPoint enemy::getpos(){
    return this->enemy_pos_current;
}

//敌人被清除
void enemy::get_removed(){
    if(num==4){
        if(die_num==1){
            if(this->tower_attacked_list.empty()){
                return;
            }
            else{
                foreach(tower *tow,tower_attacked_list){
                    tow->enemy_killed();
                }
                game->remove_enemy(this);
            }
        }
        else{
            die_num+=1;
            this->Hp_current=Hp_max;
        }
    }
    else{
        if(this->tower_attacked_list.empty()){
            return;
        }
        else{
            foreach(tower *tow,tower_attacked_list){
                tow->enemy_killed();
            }
            game->remove_enemy(this);
        }
    }
}

void enemy::get_damaged(int dam_hp){
    Hp_current-=dam_hp;
    if(Hp_current<=0){
        get_removed();
        game->money_reward();
        QMediaPlayer *reward=new QMediaPlayer;
        reward->setMedia(QUrl(":/music/material/gold.mp3"));
        reward->setVolume(30);
        reward->play();
    }
}

void enemy::doActivate(){
    is_active=true;
}

void enemy::add_tower_attacked(tower *tow){
    this->tower_attacked_list.push_back(tow);
}

void enemy::get_lose_sight(tower *tow){
    this->tower_attacked_list.removeOne(tow);
}

void enemy::set_cur_pos(QPoint p){
    enemy_pos_current=p;
}

enemy::~enemy(){
    QMediaPlayer *ene_dead=new QMediaPlayer;
    ene_dead->setMedia(QUrl(":/music/material/enemy_dead.mp3"));
    ene_dead->setVolume(30);
    ene_dead->play();
}
