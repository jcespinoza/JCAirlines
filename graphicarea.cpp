#include "graphicarea.h"

GraphicArea::GraphicArea(QWidget *parent) :
    QWidget(parent)
{

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
    if(e->button() == Qt::RightButton){
        if(closest != 0)
            emit rightClickedValid(QPoint( closest->x()+16, closest->y()+32 ));
    }else{
        if(closest != 0)
            emit clickedExisting(QPoint( closest->x()+16, closest->y()+32 ));
        else
            emit clickedEmpty(e->pos());
    }

}

void GraphicArea::createPoint(QPoint p)
{
    PointFigure *point = new PointFigure();
    connect(this, SIGNAL(highlightPoint(QPoint,QPoint)), point, SLOT(highlight(QPoint,QPoint)));
    connect(this, SIGNAL(resetGraphics()), point, SLOT(resetState()));
    point->setGeometry(QRect(p.x()-16,p.y()-32, 32, 32));
    figures.append(point);
    point->setParent(this);
    update();
}

void GraphicArea::createLine(QPoint st, QPoint en)
{
    LineFigure* line = new LineFigure();
    connect(this, SIGNAL(resetGraphics()), line, SLOT(resetState()));
    connect(this, SIGNAL(highlightEdge(QPoint,QPoint)),line, SLOT(highlight(QPoint,QPoint)));
    line->setStartX(st.x());
    line->setStartY(st.y());
    line->setEndX(en.x());
    line->setEndY(en.y());
    line->setGeometry(QRect(line->start(),line->end()));
    figures.prepend(line);
    update();
}

void GraphicArea::resetGraphics(int)
{
    update();
    emit resetGraphics();
}

void GraphicArea::deleteGraphicsInvolved(QPoint p)
{
    for(int i = 0; i < figures.count(); i++){
        if(figures.at(i) != 0){
            if(figures.at(i)->isRelated(p))
                figures.removeAt(i);
        }
    }
    update();
}
