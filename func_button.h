#ifndef FUNC_BUTTON_H
#define FUNC_BUTTON_H

#include "level1.h"
#include "tower.h"

#include <QWidget>
#include <QPushButton>
#include <QImage>
#include <QPoint>
#include <QPainter>

class tower;
class level1;

class func_button : public QPushButton
{
    Q_OBJECT
public:
    explicit func_button(QPoint pos, level1 *game_1, int swi);
    void draw(QPainter *painter);
    void removed();
    bool has_click_pos(QPoint pos);
    void set_tower(tower *t);
    //用于判断功能
    int get_img_height();
    int get_img_width();

    int get_switch();
    QPoint get_pos();
    ~func_button();
signals:

public slots:
private:
    QImage btn_img;
    QPoint btn_pos;
    level1 *game;
    tower *tow;
    int swit;
};

#endif // FUNC_BUTTON_H
