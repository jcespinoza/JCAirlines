#ifndef AIRPORT_H
#define AIRPORT_H
#include <QString>
#include <QPoint>

class Airport
{
public:
    QString code;
    QString City;
    QPoint location;

    void setCode(QString st){code = st;}
    QString getCode(){return code;}

    void setCity(QString st){city = st;}
    QString getCity(){return city;}

    void setLocation(QPoint p){location = p;}
    QPoint getLocation(){return location;}

};

#endif // AIRPORT_H
