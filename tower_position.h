#ifndef TOWER_POSITION_H
#define TOWER_POSITION_H

#include <QPoint>
#include <QPixmap>
#include <QString>
//����������
class tower_position
{
public:
    tower_position(QPoint _pos);
    void set_tow(QPainter *painter);
    //��������
    bool has_tower_pos(QPoint p);
    //�ж�p����������
    bool has_tower();
    //�жϴ˴��������޷���������
    void set_has_tow();
    //����������
    QPoint get_pos();
    //��ȡ����λ��
private:
    QPoint tow_pos;
    QPixmap tow_image;
    bool has_tow;
};

#endif // TOWER_POSITION_H
