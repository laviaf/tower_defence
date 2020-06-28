#include "world_map.h"
#include "start_click.h"
#include "mainwindow.h"
#include "level1.h"

#include <QMediaPlayer>
#include <QPixmap>
#include <QWidget>
#include <QPainter>

#include <iostream>
#include <QDebug>
using namespace std;

world_map::world_map(MainWindow *main)
{
    this->setFixedSize(1000,626);

    //第一关按钮
    start_click *btn1 = new start_click(":/material/paki.png");
    btn1->setParent(this);
    btn1->move(750,150);

    //第二关按钮
    //不好意思第二关还没做
    start_click *btn2 =new start_click(":/material/cp9.png");
    btn2->setParent(this);
    btn2->move(300,300);

    start_click *return_btn = new start_click(":/material/return.png");
    return_btn->setParent(this);
    return_btn->move(50,50);

    //连接第一关和世界地图
    connect(btn1,&QPushButton::clicked,this,[=](){
        lev1_map=new level1(this);
        this->hide();
        lev1_map->show();
        //切换背景音乐
        lev1_map->play_music();
        main->mute_music();
    });

    //连接世界地图与主界面
    connect(return_btn,&QPushButton::clicked,this,[=](){
        this->hide();
        main->show();
    });
}

void world_map::paintEvent(QPaintEvent *event){
    QPixmap wld_map;
    QPainter *painter = new QPainter;
    painter->begin(this);
    wld_map.load(":/material/world_map.jpg");
    painter->drawPixmap(0,0,this->width(),this->height(),wld_map);
    painter->end();
    delete painter;
}
