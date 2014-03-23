#ifndef LINEFIGURE_H
#define LINEFIGURE_H

#include "figure.h"

class LineFigure: public Figure
{
public:
    LineFigure();
    int x(){return xi;}
    int y(){return yi;}
    QPoint start(){return QPoint(xi,yi);}
    int endX(){return dx;}
    int endY(){return dy;}
    QPoint end(){return QPoint(dx,dy);}
    int width(){return wi;}
    int height(){return hi;}
    void setX(int val){xi = val;}
    void setY(int val){yi = val;}
    void setEndX(int val){dx = val;}
    void setEndY(int val){dy = val;}
    void setWidth(int val){wi = val;}
    void setHeight(int val){hi = val;}
    QRect geometry(){return QRect(xi,yi,wi,hi);}
    void setGeometry(QRect t){
        xi = t.x();
        yi = t.y();
        wi = t.width();
        hi = t.height();
    }
    void draw(QPainter *p){
        QPainterPath path;
        path.moveTo(start());
        path.quadTo(start(), end());

        p->drawPath(path);
    }

    bool isRelated(QPoint p){
        return start() == p || end() == p;
    }

protected:
    int xi;
    int yi;
    int wi;
    int hi;
    int dx;
    int dy;
};

#endif // LINEFIGURE_H
