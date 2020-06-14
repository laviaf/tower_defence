#include "utility.h"

#include <math.h>

utility::utility()
{
}

bool utility::collisionRange(QPoint a1, double r1, QPoint a2, double r2){
    double x=a1.x()-a2.x();
    double y=a1.y()-a2.y();
    double dis=sqrt(x*x+y*y);
    if(fabs(dis-r1-r2)<0.001)
        return true;
    else
        return false;
}
