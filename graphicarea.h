#ifndef GRAPHICAREA_H
#define GRAPHICAREA_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "pointfigure.h"
#include "linefigure.h"


class GraphicArea : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicArea(QWidget *parent = 0);
    PointFigure* getClosest(QPoint);

signals:
    void doubleClicked(QPoint);
    void clickedEmpty(QPoint);
    void clickedExisting(QPoint);
    void rightClickedValid(QPoint);
    void resetGraphics();
    void highlightPoint(QPoint,QPoint);
    void highlightEdge(QPoint,QPoint);

public slots:
    void createPoint(QPoint);
    void deleteGraphicsInvolved(QPoint p);
    void createLine(QPoint,QPoint);
    void resetGraphics(int);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    QList<Figure*> figures;
};

#endif // GRAPHICAREA_H
