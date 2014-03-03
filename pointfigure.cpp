#include "pointfigure.h"

PointFigure::PointFigure()
{

}

void PointFigure::draw(QPainter *painter)
{
    QPixmap image(":/graphics/img/greenmarker.png");
    painter->drawPixmap(x(), y(), width(), height(), image);
}
