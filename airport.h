#ifndef AIRPORT_H
#define AIRPORT_H
#include <QString>
#include <QPoint>
#include <math.h>
#include <QDebug>

class Airport
{
public:
    QString code;
    QString city;
    QPoint location;

    friend QDebug operator<< (QDebug q, const Airport &a){
        q << a.code << a.city;
        return q;
    }

    void setCode(QString st){code = st;}
    QString getCode()const {return code;}

    void setCity(QString st){city = st;}
    QString getCity() const {return city;}

    void setLocation(QPoint p){location = p;}
    QPoint getLocation() const {return location;}

    bool operator==(const Airport &other){
        return (*this).getLocation() == other.getLocation()
                || (*this).getCode() == other.getCode();
    }

    bool isWithinRange(Airport other, double range){
        return distanceFrom(other) <= range;
    }

    double distanceFrom(Airport other){
        double dx = location.x() - other.location.x();
        double dy = location.y() - other.location.y();
        dx = dx*dx;
        dy = dy*dy;
        return sqrt(dx+dy);
    }
};

#endif // AIRPORT_H
