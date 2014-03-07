#include "pointfigure.h"

PointFigure::PointFigure()
{

}

void PointFigure::draw(QPainter *painter)
{
    QPixmap image(":/graphics/img/greenmarker.png");
    painter->drawPixmap(x(), y(), width(), height(), image);
}

const double PointFigure::distance(QPoint p1, QPoint p2)
{
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
