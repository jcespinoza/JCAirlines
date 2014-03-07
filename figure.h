#ifndef FIGURE_H
#define FIGURE_H
#include <QObject>
#include <QPainter>
#include <QDebug>
#include <math.h>

class Figure: public QObject
{
    Q_OBJECT
public:
    Figure();
    virtual void draw(QPainter*) = 0;
};

#endif // FIGURE_H
