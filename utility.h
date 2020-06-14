#ifndef UTILITY_H
#define UTILITY_H

#include <QPoint>

class utility
{
public:
    utility();
    bool collisionRange(QPoint a1, double r1, QPoint a2, double r2);
};

#endif // UTILITY_H
