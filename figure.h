#ifndef FIGURE_H
#define FIGURE_H
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <math.h>

class Figure: public QWidget
{
    Q_OBJECT
public:
    Figure(){
        setToolTip("I'm a figure");
    }
    virtual void draw(QPainter*) = 0;
    virtual bool isRelated(QPoint) = 0;
    enum FigureType{POINT, LINE};
    virtual FigureType figureType() = 0;

    static double distance(QPoint p1, QPoint p2){
        int x1 = p1.x();
        int y1 = p1.y();
        int x2 = p2.x();
        int y2 = p2.y();

        int dx = x2 - x1;
        int dy = y2 - y1;

        int dx2 = pow(dx, 2);
        int dy2 = pow(dy, 2);

        int distance = sqrt(dx2+dy2);

        return distance;
    }
};

#endif // FIGURE_H
