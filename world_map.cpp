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

world_map::world_map(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1000,626);

    //第一关按钮
    start_click *btn1 = new start_click(":/material/paki.png");
    btn1->setParent(this);
    btn1->move(750,150);

    //连接第一关和世界地图
    lev1_map=new level1;
    connect(btn1,&QPushButton::clicked,this,[=](){
        this->hide();
        lev1_map->show();
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
