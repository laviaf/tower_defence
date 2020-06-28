#include "level1.h"
#include "mainwindow.h"
#include "start_click.h"
#include "tower_position.h"
#include "enemy.h"
#include "way_point.h"
#include "tower.h"
#include "func_button.h"

#include <QPainter>
#include <QMediaPlayer>
#include <QList>
#include <QTimer>

class start_click;

#include <iostream>
using namespace std;

//设定防御塔价格
static const int tower_cost1 = 300;
static const int tower_cost2 = 200;

double ene_start_interval[22]={300,800,1700,3000,4000,
                               5000,6000,7500,9000,10500,
                               12000,13500,15000,16500,18000,
                               19500,21000,22500,24000,25500,27000,28500};

int factorial(int wave){
    int i=0;
    int res=1;
    for(i=0;i<wave+1;i++){
        res=res*2;
    }
    return res-1;
}

level1::level1(world_map *map) :
    cur_wave(0),wave_total(8),money(1000),life(7),w_map(map),game_win(false),game_end(false)
{
    lose = new lose_window;
    win = new win_window;
    this->setFixedSize(1000,626); 

    load_tower_position();
    set_route();//设定航线

    //刷新界面 updateScene实现敌人运动 赋予防御塔敌人
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(40);

    // 设置3s后游戏启动
    QTimer::singleShot(3000, this, SLOT(start_game()));
}

void level1::paintEvent(QPaintEvent *event){

    QPainter *painter = new QPainter;
    painter->begin(this);

    if (game_win || game_end)
    {
        if(game_end){
            lose->draw(painter);
        }
        else if(game_win){
            win->draw(painter);
        }
        painter->end();
        delete painter;
        return;
    }
    //绘制第一关地图
    QPixmap lev1_map;
    lev1_map.load(":/material/map5.png");
    painter->drawPixmap(0,0,this->width(),this->height(),lev1_map);

    //绘制塔基 防御塔 敌人 子弹
    foreach (tower_position pos,tow_base_list)
    {
        if(!pos.has_tower())
            pos.draw(painter);
    }
    foreach (tower *tow, tower_list) {
        tow->draw(painter);
    }
    foreach (enemy *ene, enemy_list) {
        ene->draw(painter);
    }
    foreach (bullet *bul, bullet_list) {
        bul->draw(painter);
    }
    foreach (func_button *btn, func_btn_list){
        btn->draw(painter);
    }

    //显示波次，金币数量，生命值
    draw_WaveMoneyLife(painter);

    painter->end();
    delete painter;
}

void level1::play_music(){
    QMediaPlayer *lev1_music=new QMediaPlayer;
    lev1_music->setMedia(QUrl("qrc:/music/material/music2.mp3"));
    lev1_music->setVolume(30);
    lev1_music->play();
}

void level1::load_tower_position(){
    QPoint pos[8]={
        QPoint(210,230),
        QPoint(210,350),
        QPoint(310,350),
        QPoint(465,180),
        QPoint(600,180),
        QPoint(740,180),
        QPoint(900,270),
        QPoint(740,410)
    };
    int i=0,len=8;
    for(i=0;i<len;i++){
        tow_base_list.push_back(pos[i]);
    }
}

//获得敌人波次
bool level1::loadwave(){
    //如果波次结束
    if(cur_wave+1>wave_total)
        return false;
    else{
        if(cur_wave<3){
            //前三波产生小兵1
            for(int i=0;i<6+factorial(cur_wave);i++){
                way_point *start=route.back();
                enemy *ene= new enemy(start,1,this);
                enemy_list.push_back(ene);
                QTimer::singleShot(ene_start_interval[i],ene,SLOT(doActivate()));
            }
        }
        else if(cur_wave>=3&&cur_wave<6){
            int i=0;
            for(i=0;i<6;i++){
                way_point *start=route.back();
                enemy *ene= new enemy(start,2,this);
                enemy_list.push_back(ene);
                QTimer::singleShot(ene_start_interval[i],ene,SLOT(doActivate()));
            }
            for(i=6;i<cur_wave*2+6;i++){
                way_point *start=route.back();
                enemy *ene= new enemy(start,3,this);
                enemy_list.push_back(ene);
                QTimer::singleShot(ene_start_interval[i],ene,SLOT(doActivate()));
            }
        }
        else if(cur_wave==6){
            int i=0;
            for(i=0;i<3;i++){
                way_point *start=route.back();
                enemy *ene= new enemy(start,1,this);
                enemy_list.push_back(ene);
                QTimer::singleShot(ene_start_interval[i],ene,SLOT(doActivate()));
            }
            for(i=3;i<7;i++){
                way_point *start=route.back();
                enemy *ene= new enemy(start,2,this);
                enemy_list.push_back(ene);
                QTimer::singleShot(ene_start_interval[i],ene,SLOT(doActivate()));
            }
            for(i=6;i<11;i++){
                way_point *start=route.back();
                enemy *ene= new enemy(start,3,this);
                enemy_list.push_back(ene);
                QTimer::singleShot(ene_start_interval[i],ene,SLOT(doActivate()));
            }
        }
        else if(cur_wave==7){
            way_point *start=route.back();
            enemy *ene= new enemy(start,4,this);
            enemy_list.push_back(ene);
            QTimer::singleShot(ene_start_interval[0],ene,SLOT(doActivate()));
        }
        else{}
        return true;
    }
}

//设定第一关路径
void level1::set_route(){
    //逆序路径
    way_point *Point1 = new way_point(QPoint(910,530));
    route.push_back(Point1);
    way_point *Point2 = new way_point(QPoint(820,530));
    route.push_back(Point2);
    Point2->setNextWayPoint(Point1);
    way_point *Point3 = new way_point(QPoint(820,105));
    route.push_back(Point3);
    Point3->setNextWayPoint(Point2);
    way_point *Point4 = new way_point(QPoint(380,105));
    route.push_back(Point4);
    Point4->setNextWayPoint(Point3);
    way_point *Point5 = new way_point(QPoint(380,415));
    route.push_back(Point5);
    Point5->setNextWayPoint(Point4);
    way_point *Point6 = new way_point(QPoint(140,415));
    route.push_back(Point6);
    Point6->setNextWayPoint(Point5);
    way_point *Point7 = new way_point(QPoint(140,160));
    route.push_back(Point7);
    Point7->setNextWayPoint(Point6);
    way_point *Point8 = new way_point(QPoint(0,155));
    route.push_back(Point8);
    Point8->setNextWayPoint(Point7);
}

//控制更新界面 敌人开始运动 炮塔选择敌人
void level1::updateScene(){
    foreach (enemy* ene,this->enemy_list) {
        ene->move();
    }
    foreach(tower* tow,this->tower_list){
        tow->is_enemy_can_attack();
    }
    update();
}

//鼠标事件 建塔/拆塔/升级
void level1::mousePressEvent(QMouseEvent *event){
    QPoint mouse_pos=event->pos();
    cout<<mouse_pos.x()<<' '<<mouse_pos.y()<<endl;
    auto it=tow_base_list.begin();
    while(it!=tow_base_list.end()){
        //鼠标左键用于建塔/升级/移除
        if(event->button()==Qt::LeftButton){
            //如果这点有塔基+这个塔基上无塔+这个塔基处无按钮,表明此处可建塔->构造选择按钮
            if(it->has_tower_pos(mouse_pos)&&(!it->has_tower())&&(!it->has_fun_btn())){
                func_button *btn=new func_button(mouse_pos,this,1);
                it->set_fun_btn(btn);
                this->func_btn_list.push_back(btn);
                update();
                break;
            }
            //有选择按钮2+按钮范围内点击
            else if(it->has_fun_btn()&&it->get_fun_btn()->has_click_pos(mouse_pos)&&(it->get_fun_btn()->get_switch()==2)){
                if(mouse_pos.y()<it->get_fun_btn()->get_img_height()/2+it->get_fun_btn()->get_pos().y()){
                    //实现升级功能
                    if(money-it->get_tower_info()->get_updatecost()>=0){
                    money-=it->get_tower_info()->get_updatecost();
                    it->get_tower_info()->upgrade();
                    update();
                    }
                }
                else{
                    //实现防御塔拆除
                    restruct_money_reward(it->get_tower_info());
                    it->get_tower_info()->removed();
                    it->set_tower(NULL);
                    it->removed_tow();
                }
                //拆除选择按钮
                it->get_fun_btn()->removed();
                it->set_fun_btn(NULL);
                update();
                break;
            }
            //有选择按钮1+点击了选择按钮->判断建塔
            else if(it->has_fun_btn()&&it->get_fun_btn()->has_click_pos(mouse_pos)&&(it->get_fun_btn()->get_switch()==1)){
                if(mouse_pos.x()<it->get_fun_btn()->get_pos().x()+it->get_fun_btn()->get_img_width()/2){
                    //如果点击的是第一个塔
                    //塔的顺序不小心写反了
                    if(can_buy_tower(2)){
                        it->set_has_tow();
                        tower *tow=new tower(it->get_pos(),2,this);
                        it->set_tower(tow);
                        tower_list.push_back(tow);
                        money-=tower_cost2;
                        updateScene();
                    }
                }
                else{
                    //如果点击的是第二个塔
                    if(can_buy_tower(1)){
                        it->set_has_tow();
                        tower *tow=new tower(it->get_pos(),1,this);
                        it->set_tower(tow);
                        tower_list.push_back(tow);
                        money-=tower_cost1;
                        updateScene();
                    }
                }
                //拆除选择按钮
                it->get_fun_btn()->removed();
                it->set_fun_btn(NULL);
                update();
                break;
            }
            else{}
        }
        //鼠标右键用于产生拆塔及升级按钮
        else if(event->button()==Qt::RightButton){
            //如果鼠标点有塔基+这个塔基没有选择按钮+这个塔基上有塔->产生升级按钮
            if(it->has_tower_pos(mouse_pos)&&(!it->has_fun_btn())&&it->has_tower()){
                func_button *btn=new func_button(mouse_pos,this,2);
                it->set_fun_btn(btn);
                this->func_btn_list.push_back(btn);
                btn->set_tower(it->get_tower_info());
                update();
                break;
            }
        }
        it++;
    }
}

//相关图标
void level1::draw_WaveMoneyLife(QPainter *painter){
    life_.load(":/material/life.png");
    gold_.load(":/material/gold.png");
    wave_.load(":/material/wave.png");

    painter->save();

    painter->drawImage(250,20,life_);
    painter->drawImage(400,20,gold_);
    painter->drawImage(570,20,wave_);
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(QPoint(310,25),QPoint(410,45)),QString("Life : %1").arg(life));
    painter->drawText(QRect(QPoint(460,25),QPoint(560,45)),QString("Gold : %1").arg(this->money));
    painter->drawText(QRect(QPoint(650,25),QPoint(750,45)),QString("Wave : %1").arg(cur_wave+1));

    painter->restore();
}

bool level1::can_buy_tower(int s){
    switch (s) {
    case 1:{
        if(this->money>=tower_cost1)
            return true;
        else
            return false;
    }
    case 2:{
        if(this->money>=tower_cost2)
                return true;
            else
                return false;
        break;
    }
    default:
        break;
    }
}

void level1::money_reward(){
    this->money+=70;
}

void level1::restruct_money_reward(tower *t){
    money+=t->get_destruct_bonus();
}

//减少我方基地生命
void level1::damage_life(){
    life-=1;
    if(life<=0){
        if(!game_end){
            game_end=true;
        }
    }
}

//加载第一波敌人
void level1::start_game(){
    loadwave();
}

//为了在界面中画出子弹
void level1::add_bullet(bullet *bul){
    this->bullet_list.push_back(bul);
}

void level1::remove_bullet(bullet* bul){
    Q_ASSERT(bul);

    bullet_list.removeOne(bul);
    delete bul;
}

//清除敌人 若此波敌人清空 加载下一波
void level1::remove_enemy(enemy *ene){
    Q_ASSERT(ene);
    enemy_list.removeOne(ene);
    delete ene;
    if(this->enemy_list.empty()){
        this->cur_wave+=1;
        if(!loadwave())
        {
            game_win=true;
            //paintevent中调用胜利界面
        }
        else{}
    }
}

void level1::remove_func_btn(func_button *btn){
    Q_ASSERT(btn);
    this->func_btn_list.removeOne(btn);
    delete btn;
}

void level1::remove_tower(tower *t){
    Q_ASSERT(t);
    this->tower_list.removeOne(t);
    delete t;
}

QList<enemy*> level1::get_ene_list(){
    return enemy_list;
}

