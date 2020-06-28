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

    //��һ�ذ�ť
    start_click *btn1 = new start_click(":/material/paki.png");
    btn1->setParent(this);
    btn1->move(750,150);

    //�ڶ��ذ�ť
    //������˼�ڶ��ػ�û��
    start_click *btn2 =new start_click(":/material/cp9.png");
    btn2->setParent(this);
    btn2->move(300,300);

    start_click *return_btn = new start_click(":/material/return.png");
    return_btn->setParent(this);
    return_btn->move(50,50);

    //���ӵ�һ�غ������ͼ
    connect(btn1,&QPushButton::clicked,this,[=](){
        lev1_map=new level1(this);
        this->hide();
        lev1_map->show();
        //�л���������
        lev1_map->play_music();
        main->mute_music();
    });

    //���������ͼ��������
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
