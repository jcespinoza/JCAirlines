#ifndef AIRPORT_H
#define AIRPORT_H
#include <QString>
#include <QPoint>

class Airport
{
public:
    QString code;
    QString city;
    QPoint location;

    void setCode(QString st){code = st;}
    QString getCode()const {return code;}

    void setCity(QString st){city = st;}
    QString getCity() const {return city;}

    void setLocation(QPoint p){location = p;}
    QPoint getLocation() const {return location;}

    bool operator ==(const Airport &other){
        return (*this).getLocation() == other.getLocation();
    }
};

#endif // AIRPORT_H
