#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "graphicarea.h"
#include "airport.h"
#include "../GrafoTest/Grafo.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace Ui {
class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = 0);
    ~AdminDialog();

private:
    Ui::AdminDialog *ui;
    void initializeGraphics();
    GraphicArea *gArea;
    void doConnects();
    Graph<Airport>* airports;
    Airport getFromPoint(QPoint);
signals:
    void pointApproved(QPoint);

public slots:
    void requestInfo(QPoint);
    void showConnection(QPoint);
    void saveFileToXML();
};

#endif // ADMINDIALOG_H
