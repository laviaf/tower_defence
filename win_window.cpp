#include "win_window.h"

win_window::win_window(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1000,626);
    img.load(":/material/win_.jpg");
}

void win_window::draw(QPainter *painter){
    painter->drawImage(QRect(0,0,this->width(),this->height()),img);
}
