#include "way_point.h"

way_point::way_point(QPoint pos)
    : m_pos(pos)
    , m_nextWayPoint(NULL)
{
}

void way_point::setNextWayPoint(way_point *nextPoint)
{
    m_nextWayPoint = nextPoint;
}

way_point* way_point::nextWayPoint() const
{
    return m_nextWayPoint;
}

const QPoint way_point::getpos() const
{
    return m_pos;
}
