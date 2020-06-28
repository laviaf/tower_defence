#ifndef UTILITY_H
#define UTILITY_H

#include <QPoint>
#include <math.h>

class utility
{
public:
    utility();
    inline bool collisionRange(QPoint a1, double r1, QPoint a2, double r2){
        double x=a1.x()-a2.x();
        double y=a1.y()-a2.y();
        double dis=sqrt(x*x+y*y);
        if(r1+r2-dis>=0)
            return true;
        else
            return false;
    }
};

#endif // UTILITY_H
