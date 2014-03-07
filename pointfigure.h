#ifndef POINTFIGURE_H
#define POINTFIGURE_H
#include "figure.h"

class PointFigure: public Figure
{
public:
    PointFigure();
    void draw(QPainter *);
    int x(){return xi;}
    int y(){return yi;}
    int width(){return wi;}
    int height(){return hi;}
    void setX(int val){xi = val;}
    void setY(int val){yi = val;}
    void setWidth(int val){wi = val;}
    void setHeight(int val){hi = val;}
    QRect geometry(){return QRect(xi,yi,wi,hi);}
    void setGeometry(QRect t){
        xi = t.x();
        yi = t.y();
        wi = t.width();
        hi = t.height();
    }

    static const double distance(QPoint,QPoint);

protected:
    int xi;
    int yi;
    int wi;
    int hi;
};

#endif // POINTFIGURE_H
