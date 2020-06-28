#ifndef TOWER_POSITION_H
#define TOWER_POSITION_H

#include "func_button.h"
#include "tower.h"

#include <QPoint>
#include <QPixmap>
#include <QString>
//����������

class func_button;
class tower;

class tower_position
{
public:
    tower_position(QPoint _pos);
    void draw(QPainter *painter);
    //��������
    bool has_tower_pos(QPoint p);
    //�ж�p����������
    bool has_tower();
    //�жϴ˴��������޷���������
    void set_has_tow();
    //����������
    void removed_tow();
    //����������
    QPoint get_pos();
    //��ȡ����λ��
    void set_tower(tower* t);
    //���������������λ��
    func_button* get_fun_btn();
    bool has_fun_btn();
    void set_fun_btn(func_button *btn);
    tower* get_tower_info();
private:
    QPoint tow_pos;
    QPixmap tow_image;
    bool has_tow;

    func_button *fun_btn;
    tower* tow;
};

#endif // TOWER_POSITION_H
