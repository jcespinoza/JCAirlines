#ifndef POINTFIGURE_H
#define POINTFIGURE_H
#include "figure.h"

class PointFigure: public Figure
{
public:
    PointFigure(){
        imgPath = ":/graphics/img/greenmarker.png";
    }
    void draw(QPainter *painter){
        QPixmap image(imgPath);
        painter->drawPixmap(x(), y(), width(), height(), image);
    }

    int x(){return xi;}
    int y(){return yi;}
    QPoint point(){return QPoint(xi,yi);}
    int width(){return wi;}
    int height(){return hi;}
    void setX(int val){xi = val;}
    void setY(int val){yi = val;}
    void setWidth(int val){wi = val;}
    void setHeight(int val){hi = val;}
    QRect geometry(){return QRect(xi,yi,wi,hi);}

    bool isRelated(QPoint p){
        return point() == p || QPoint(xi+16,yi+32) == p;
    }

    FigureType figureType(){
        return POINT;
    }

    void setGeometry(QRect t){
        xi = t.x();
        yi = t.y();
        wi = t.width();
        hi = t.height();
    }
public slots:
    void resetState(){
        imgPath = ":/graphics/img/greenmarker.png";
    }

    void highlight(QPoint st, QPoint){
        if(isRelated(st))
            imgPath = ":/graphics/img/bluemarker.png";
    }

protected:
    int xi;
    int yi;
    int wi;
    int hi;
    QString imgPath;
};

#endif // POINTFIGURE_H
