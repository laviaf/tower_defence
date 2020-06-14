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
    //��һ������
    loadwave(7);
}

void level1::paintEvent(QPaintEvent *event){
    //���Ƶ�һ�ص�ͼ
    QPixmap lev1_map;
    QPainter *painter = new QPainter;
    painter->begin(this);
    lev1_map.load(":/material/map_101.jpg");
    painter->drawPixmap(0,0,this->width(),this->height(),lev1_map);

    //��������
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

    //���Ʒ�����
    foreach (tower *tow, tower_list) {
        tow->draw(painter);
    }

    //����draw��������
    //����ǰ������
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


//��õ��˲���
void level1::loadwave(int ene_num){
    //ÿ1.5�����get_enemy()����һ������
    QTimer *get_ene_timer = new QTimer(this);
    get_ene_timer->start(1500);
    connect(get_ene_timer,&QTimer::timeout,this,[=](){
        //�������趨������Ŀ��������
        get_enemy(route);
        if(enemy_list.count()>=ene_num){
            get_ene_timer->stop();
        }
    });
}

//���һ�����˲���������б���
void level1::get_enemy(QList<way_point*> route){
    enemy *ene=new enemy(route,1);
    enemy_list.push_back(ene);
}

//�趨��һ��·��
void level1::set_route(){
    way_point *Point1 = new way_point(QPoint(1000, 240));
    route.push_back(Point1);
    way_point *Point2 = new way_point(QPoint(0, 240));
    route.push_back(Point2);
    Point1->setNextWayPoint(Point2);
}

//���Ƹ��½���
void level1::updateScene(){
    update();
}

//����¼�
//�ֽ����ڽ���
void level1::mousePressEvent(QMouseEvent *event){
    QPoint mouse_pos=event->pos();
    cout<<mouse_pos.x()<<' '<<mouse_pos.y()<<endl;
    int i=0;
    while(i<this->tow_base_list.size()){
        //��������+���������+�������������,�����˴��ɽ���
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

//���ڻ�δʵ�ֽ����ع��� ��ע��
bool level1::can_buy_tower(){
    return true;
//    if(this->money>=1000)
//        return true;
//    else
//        return false;
}
