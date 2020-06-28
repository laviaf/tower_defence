#include "func_button.h"

#include <iostream>
using namespace std;

func_button::func_button(QPoint pos, level1 *game_1,int swi) :
    QPushButton(0),btn_pos(pos),game(game_1),swit(swi),tow(NULL)
{
    switch(swit){
    case 1:{
        btn_img.load(":/material/sele_btn.png");
        break;
    }
    case 2:{
        btn_img.load(":/material/fun_btn.jpg");
        break;
    }
    default:
        break;
    }
}

void func_button::draw(QPainter *painter){
    switch (swit) {
    case 1:{
        painter->drawImage(btn_pos,btn_img);
        break;
    }
    case 2:{
        painter->drawImage(btn_pos,btn_img);
        painter->save();
        painter->setPen(QPen(Qt::black));
        if(tow->get_updatecost()!=0){
            painter->drawText(QRect(btn_pos.x(),btn_pos.y(),btn_img.width(),btn_img.height()/2),QString("update cost: %1").arg(tow->get_updatecost()));
            painter->drawText(QRect(btn_pos.x(),btn_pos.y()+btn_img.height()/2,btn_img.width(),btn_img.height()/2),QString("destruct bonus: %1").arg(tow->get_destruct_bonus()));
        }
        else{
            painter->drawText(QRect(btn_pos.x(),btn_pos.y(),btn_img.width(),btn_img.height()/2),QString("can't update"));
            painter->drawText(QRect(btn_pos.x(),btn_pos.y()+btn_img.height()/2,btn_img.width(),btn_img.height()/2),QString("destruct bonus: %1").arg(tow->get_destruct_bonus()));
        }
        painter->restore();
    }
    default:
        break;
    }
}

void func_button::removed(){
    game->remove_func_btn(this);
}

//判断是否点击功能按钮
bool func_button::has_click_pos(QPoint pos){
    bool has_x=btn_pos.x()<pos.x()&&pos.x()<btn_pos.x()+btn_img.width();
    bool has_y=btn_pos.y()<pos.y()&&pos.y()<btn_pos.y()+btn_img.height();
    return has_x&&has_y;
}

void func_button::set_tower(tower *t){
    tow=t;
}

int func_button::get_img_height(){
    return btn_img.height();
}

int func_button::get_img_width(){
    return btn_img.width();
}

int func_button::get_switch(){
    return swit;
}

QPoint func_button::get_pos(){
    return btn_pos;
}

func_button::~func_button(){
    this->game=NULL;
    this->tow=NULL;
}
