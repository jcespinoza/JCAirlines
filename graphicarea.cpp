#include "graphicarea.h"

GraphicArea::GraphicArea(QWidget *parent) :
    QWidget(parent)
{
    setToolTip("Mapa de Aeropuertos. Click para agregar uno. Click sobre uno para establecer una connexion.");

}

PointFigure *GraphicArea::getClosest(QPoint p1)
{
    double distance = -1;
    for(int i = 0; i < figures.count(); i++){
        PointFigure* temp = (PointFigure*)(figures.at(i));
        distance = PointFigure::distance(p1, QPoint(temp->x()+16,temp->y()+32) );
        if(distance < 24)
            return temp;
    }
    return 0;
}

void GraphicArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap ocean(":/graphics/img/ocean.png");
    painter.drawTiledPixmap(geometry(),ocean);

    QPixmap map(":/graphics/img/greenmap.png");
    painter.drawPixmap(geometry(),map);
    for(int i = 0; i < figures.length(); i++)
        figures.at(i)->draw(&painter);
}

void GraphicArea::mousePressEvent(QMouseEvent *e)
{
    PointFigure* closest = getClosest(e->pos());
    if(closest != 0)
        emit clickedExisting(QPoint( closest->x()+16, closest->y()+32 ));
    else
        emit clickedEmpty(e->pos());
}

void GraphicArea::createPoint(QPoint p)
{
    PointFigure *point = new PointFigure();
    point->setGeometry(QRect(p.x()-16,p.y()-32, 32, 32));
    figures.append(point);
    update();
}
