#include "level1.h"
#include "mainwindow.h"
#include "tower_position.h"
#include "enemy.h"

#include <QPainter>
#include <QMediaPlayer>
#include <QList>
#include <QTimer>

#include <iostream>
using namespace std;

level1::level1(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1000,626);

//    QMediaPlayer *lev1_music=new QMediaPlayer;
//    lev1_music->setMedia(QUrl("qrc:/music/material/music1.mp3"));
//    lev1_music->setVolume(30);

//    lev1_music->play();

}

void level1::paintEvent(QPaintEvent *event){
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
    QList<tower_position*> tow_base_list;
    int i=0,len	= sizeof(pos) / sizeof(pos[0]);
    for(i=0;i<len;i++){
        tow_base_list.push_back(new tower_position(pos[i]));
        tow_base_list[i]->set_tow(painter);
    }

    //设定敌人前进路径
    QList<QPoint*> ene_way;
    QPoint *ene_start=new QPoint(1000,300);
    QPoint *ene_end=new QPoint(0,300);
    ene_way.push_back(ene_start);
    ene_way.push_back(ene_end);

    //每一秒产生一个敌人
    QTimer *get_ene_timer = new QTimer(this);
    connect(get_ene_timer,SIGNAL(timeout()),this,SLOT(get_enemy(ene_way)));
    get_ene_timer->start(1000);
    //为什么敌人画不出来？？？


    //控制敌人前进动画
    foreach (enemy *ene, enemy_list) {
        ene->draw(painter);
        QTimer *ene_move = new QTimer(this);
        connect(ene_move, SIGNAL(timeout()), this, SLOT(updateScene()));
        ene_move->start(10);
    }

    painter->end();
    delete painter;
}


void level1::get_enemy(QList<QPoint*> ene_way){
    enemy *ene=new enemy(ene_way,":/enemy/material/enemy2.png");
    enemy_list.push_back(ene);
    ene->move();
    update();
}

//更新界面
void level1::updateScene(){
    update();
}
