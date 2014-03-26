#ifndef LINEFIGURE_H
#define LINEFIGURE_H

#include "figure.h"
#include <QDebug>

class LineFigure: public Figure
{
public:
    LineFigure(){
        color = Qt::blue;
    }
    int x(){return xi;}
    int y(){return yi;}
    QPoint start(){return QPoint(xi,yi);}
    int endX(){return dx;}
    int endY(){return dy;}
    QPoint end(){return QPoint(dx,dy);}
    int width(){return wi;}
    int height(){return hi;}
    void setStartX(int val){xi = val;}
    void setStartY(int val){yi = val;}
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
    void draw(QPainter *painter){
        QPainterPath path;
        path.moveTo(start());
        path.cubicTo(start()+QPoint(5,5), start(), end());

        QPen pen(color);
        pen.setWidth(3);
        pen.setCapStyle(Qt::RoundCap);
        painter->setPen(pen);
        painter->drawPath(path);
    }

    bool isRelated(QPoint p){
        return start() == p || end() == p;
    }

    bool isEnd(QPoint p){
        return end() == p || QPoint(dx+16,dy+32) == p;
    }

    bool isStart(QPoint p){
        return start() == p || QPoint(xi+16,yi+32) == p;
    }

    FigureType figureType(){
        return LINE;
    }

protected:
    int xi;
    int yi;
    int wi;
    int hi;
    int dx;
    int dy;
    QColor color;


public slots:
    void resetState(){
        color = Qt::blue;
    }

    void highlight(QPoint p,QPoint q){
        if(isEnd(q) && isStart(p))
            color = Qt::yellow;
    }
};

#endif // LINEFIGURE_H
