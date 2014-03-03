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

signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    QList<Figure*> figures;
};

#endif // GRAPHICAREA_H
