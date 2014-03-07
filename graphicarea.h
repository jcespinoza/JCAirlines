#ifndef GRAPHICAREA_H
#define GRAPHICAREA_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "pointfigure.h"


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

public slots:
    void createPoint(QPoint);

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    QList<Figure*> figures;
};

#endif // GRAPHICAREA_H
