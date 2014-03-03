#include "graphicarea.h"

GraphicArea::GraphicArea(QWidget *parent) :
    QWidget(parent)
{

}

void GraphicArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap whiteBG(":/graphics/img/ocean.png");
    painter.drawTiledPixmap(geometry(),whiteBG);
    //Painted the bluocean
    QPixmap map(":/graphics/img/greenmap.png");
    painter.drawPixmap(geometry(),map);
    for(int i = 0; i < figures.length(); i++)
        figures.at(i)->draw(&painter);
}

void GraphicArea::mouseDoubleClickEvent(QMouseEvent *e)
{
    PointFigure *point = new PointFigure();
    point->setGeometry(QRect(e->pos().x()-16,e->pos().y()-32, 32, 32));
    figures.append(point);
    update();
}
