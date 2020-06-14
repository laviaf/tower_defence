#ifndef WAY_POINT_H
#define WAY_POINT_H

#include <QPoint>
#include <QPainter>


class way_point
{
public:
    way_point(QPoint pos);
    void setNextWayPoint(way_point *nextPoint);//设定下一航点位置
    way_point* nextWayPoint() const; //获取下一个航点
    const QPoint getpos() const;//获得当前航点位置

private:
    QPoint m_pos; //所处航点
    way_point * m_nextWayPoint; //下个航点
};

#endif // WAY_POINT_H
