#include "level1.h"
#include "mainwindow.h"
#include "tower_position.h"
#include "enemy.h"
#include "way_point.h"
#include "tower.h"

#include <QPainter>
#include <QMediaPlayer>
#include <QList>
#include <QTimer>

#include <iostream>
using namespace std;

level1::level1(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1000,626); 
    set_route();
    //第一波进攻
    loadwave(7);
}

void level1::paintEvent(QPaintEvent *event){
    //绘制第一关地图
    QPixmap lev1_map;
    QPainter *painter = new QPainter;
    painter->begin(this);
    lev1_map.load(":/material/map_101.jpg");
    painter->drawPixmap(0,0,this->width(),this->height(),lev1_map);

    //绘制塔基
    QPoint pos[7]={
        QPoint(300,310),
        QPoint(450,310),
        QPoint(600,310),
        QPoint(750,310),
        QPoint(250,150),
        QPoint(400,150),
        QPoint(700,150)
    };
    int i=0,len	= sizeof(pos) / sizeof(pos[0]);
    for(i=0;i<len;i++){
        tow_base_list.push_back(new tower_position(pos[i]));
        tow_base_list[i]->set_tow(painter);
    }

    //绘制防御塔
    foreach (tower *tow, tower_list) {
        tow->draw(painter);
    }

    //调用draw画出敌人
    //敌人前进动画
    foreach (enemy *ene, enemy_list) {
        ene->draw(painter);
        updateScene();
        ene->move();
        QTimer *ene_timer = new QTimer(this);
        connect(ene_timer,&QTimer::timeout, this,[=](){
            this->updateScene();
        });
        ene_timer->start(50);
    }


    painter->end();
    delete painter;
}


//获得敌人波次
void level1::loadwave(int ene_num){
    //每1.5秒调用get_enemy()产生一个敌人
    QTimer *get_ene_timer = new QTimer(this);
    get_ene_timer->start(1500);
    connect(get_ene_timer,&QTimer::timeout,this,[=](){
        //按波次设定敌人数目产生敌人
        get_enemy(route);
        if(enemy_list.count()>=ene_num){
            get_ene_timer->stop();
        }
    });
}

//获得一个敌人并推入敌人列表中
void level1::get_enemy(QList<way_point*> route){
    enemy *ene=new enemy(route,1);
    enemy_list.push_back(ene);
}

//设定第一关路径
void level1::set_route(){
    way_point *Point1 = new way_point(QPoint(1000, 240));
    route.push_back(Point1);
    way_point *Point2 = new way_point(QPoint(0, 240));
    route.push_back(Point2);
    Point1->setNextWayPoint(Point2);
}

//控制更新界面
void level1::updateScene(){
    update();
}

//鼠标事件
//现仅用于建塔
void level1::mousePressEvent(QMouseEvent *event){
    QPoint mouse_pos=event->pos();
    cout<<mouse_pos.x()<<' '<<mouse_pos.y()<<endl;
    int i=0;
    while(i<this->tow_base_list.size()){
        //如果买得起+这点有塔基+这个塔基上无塔,表明此处可建塔
        if(can_buy_tower()&&tow_base_list[i]->has_tower_pos(mouse_pos)&&(!tow_base_list[i]->has_tower())){
            tow_base_list[i]->set_has_tow();
            tower *tow=new tower(tow_base_list[i]->get_pos(),1);
            tower_list.push_back(tow);
            updateScene();
            break;
        }
        i++;
    }
}

//现在还未实现金币相关功能 先注掉
bool level1::can_buy_tower(){
    return true;
//    if(this->money>=1000)
//        return true;
//    else
//        return false;
}
