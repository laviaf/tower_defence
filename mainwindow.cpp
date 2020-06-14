#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "start_click.h"
#include "world_map.h"
#include <QWidget>
#include <QtMultimedia/qmediaplayer.h>

#include <QDebug>
#include <iostream>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(1000,626);
    ui->setupUi(this);

    QMediaPlayer *main_music=new QMediaPlayer;
    main_music->setMedia(QUrl("qrc:/material/music_main.mp3"));
    main_music->setVolume(30);
    main_music->play();
    //设置背景音乐

    start_click *click=new start_click(":/material/action_button.png");
    click->setParent(this);
    click->move(420,400);
    //开始按钮

    map=new world_map;
    connect(click,&QPushButton::clicked,this,[=](){
        this->hide();
        map->show();
        //更换背景音乐
        main_music->setVolume(0);
        QMediaPlayer *lev1_music=new QMediaPlayer;
        lev1_music->setMedia(QUrl("qrc:/music/material/music1.mp3"));
        lev1_music->setVolume(30);
        lev1_music->play();
    });
    //连接开始按钮和世界地图
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter draw_mainwindow(this);
    QPixmap image_mainwindow;
    image_mainwindow.load(":/material/main_window.jpg");
    draw_mainwindow.drawPixmap(0,0,this->width(),this->height(),image_mainwindow);
}

void MainWindow::updateScene(){
    update();
}
