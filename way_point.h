#ifndef WAY_POINT_H
#define WAY_POINT_H

#include <QPoint>
#include <QPainter>


class way_point
{
public:
    way_point(QPoint pos);
    void setNextWayPoint(way_point *nextPoint);//�趨��һ����λ��
    way_point* nextWayPoint() const; //��ȡ��һ������
    const QPoint getpos() const;//��õ�ǰ����λ��

private:
    QPoint m_pos; //��������
    way_point * m_nextWayPoint; //�¸�����
};

#endif // WAY_POINT_H
