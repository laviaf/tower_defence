#include "lose_window.h"

lose_window::lose_window(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1000,626);
    img.load(":/material/lose.jpg");
}

void lose_window::draw(QPainter *painter){
    painter->drawImage(QRect(0,0,this->width(),this->height()),img);
}
