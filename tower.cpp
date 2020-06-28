#include "tower.h"
#include "utility.h"

#include <QList>
#include <iostream>
using namespace std;

class utility;

tower::tower(QPoint pos,int t_num,level1 *game_1):
    t_pos(pos),attacked_enemy(NULL),game(game_1),choose(t_num),grade(0)
{
    switch (choose) {
    case 1://·ÀÓùËþ1
    {
        t_img.load(":/tower/material/crew_lufu_1.png");
        this->fire_rate=1000;//¿ªÅÚ¼ä¸ô
        this->attack_range=100;
        this->damage=40;
        this->update_cost=200;
        this->destruct_bonus=100;
        break;
    }
    case 2://·ÀÓùËþ2
    {
        t_img.load(":/tower/material/zoro.png");
        this->fire_rate=1000;
        this->attack_range=105;
        this->damage=35;
        this->update_cost=150;
        this->destruct_bonus=100;
        break;
    }
    default:
        break;
    }
    shoot_timer=new QTimer(this);
    connect(shoot_timer, SIGNAL(timeout()), this, SLOT(shoot_bullet()));
}

void tower::upgrade(){
    switch (choose) {
    case 1:{
        if(grade==0){
            //·ÀÓùËþ1Éý¼¶1
            t_img.load(":/tower/material/crew_lufu_upgrade2.png");
            this->fire_rate=800;
            this->attack_range=150;
            this->damage=70;
            this->update_cost=300;
            this->destruct_bonus=200;
            this->grade=1;
            break;
        }
        else if(grade==1){
            //·ÀÓùËþ1Éý¼¶2
            this->fire_rate=650;
            this->attack_range=170;
            this->damage=150;
            this->update_cost=0;
            this->destruct_bonus=400;
            this->grade=2;
            break;
        }
    }
    case 2:{
        if(grade==0){
            //·ÀÓùËþ2Éý¼¶1
            t_img.load(":/tower/material/zoro_update.png");
            this->fire_rate=900;
            this->attack_range=130;
            this->damage=60;
            this->update_cost=200;
            this->destruct_bonus=150;
            this->grade=1;
            break;
        }
        else if(grade==1){
            //·ÀÓùËþ2Éý¼¶2
            this->fire_rate=800;
            this->attack_range=140;
            this->damage=110;
            this->update_cost=0;
            this->destruct_bonus=200;
            this->grade=2;
            break;
        }
    }
    default:
        break;
    }
}

//¼ì²éµÐÈË±»¹¥»÷×´Ì¬
void tower::is_enemy_can_attack(){
    utility check;//ÓÃÓÚÅÐ¶ÏÊÇ·ñ½øÈë¹¥»÷·¶Î§
    if(attacked_enemy){
        //Ê§È¥µÐÈËÊÓÒ°
        if (!check.collisionRange(this->t_pos,(double)attack_range,attacked_enemy->getpos(),1))
            lose_sight();
    }
    else{
        QList<enemy*> ene_list=game->get_ene_list();
        foreach(enemy* ene,ene_list){
            if(check.collisionRange(this->t_pos,(double)attack_range,ene->getpos(),0)){
                get_attacked_enemy(ene);
                break;
            }
        }
    }
}

void tower::draw(QPainter *painter){
    painter->save();

    //»­³ö¹¥»÷·¶Î§
    painter->setPen(Qt::red);
    QPoint center(t_pos.x()+24,t_pos.y()+24);
    painter->drawEllipse(center,attack_range,attack_range);
    painter->drawImage(t_pos.x(),t_pos.y(),t_img);

    painter->restore();
}

void tower::attack(){
    shoot_timer->start(this->fire_rate);
}

//»ñµÃ±»¹¥»÷µÐÈË
void tower::get_attacked_enemy(enemy *ene){
    attacked_enemy=ene;
    attack();
    ene->add_tower_attacked(this);
}

void tower::lose_sight(){
    attacked_enemy->get_lose_sight(this);
    if (attacked_enemy)
        attacked_enemy = NULL;
    this->shoot_timer->stop();
}

//·¢Éä×Óµ¯²¢ÊµÏÖ×Óµ¯ÒÆ¶¯
void tower::shoot_bullet(){
    bullet *bul=new bullet(t_pos,attacked_enemy->getpos(),this->damage,attacked_enemy,game);
    bul->move();
    game->add_bullet(bul);
}

void tower::enemy_killed(){
    if(attacked_enemy){
        attacked_enemy=NULL;
    }
    this->shoot_timer->stop();
    //ËþÐý»ØÕýÎ»¹¦ÄÜ´ýÁôÊµÏÖ
}

void tower::removed(){
    if(attacked_enemy!=NULL){
        attacked_enemy->get_lose_sight(this);
        attacked_enemy==NULL;
    }
    game->remove_tower(this);
}

int tower::get_updatecost(){
    return this->update_cost;
}

int tower::get_destruct_bonus(){
    return this->destruct_bonus;
}
