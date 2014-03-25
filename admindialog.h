#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "graphicarea.h"
#include "airport.h"
#include "../GrafoTest/Grafo.h"

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
    Airport getFromCode(QString);
    QString xmlPath;
    void closeEvent(QCloseEvent*);
    bool modified;

signals:
    void pointApproved(QPoint);
    void addLine(QPoint,QPoint);
    void deleteApproved(QPoint);

public slots:
    void requestInfo(QPoint);
    void requestDelete(QPoint);
    void showConnection(QPoint);
    void saveFileToXML();
    void loadFromXML();
private slots:
    void on_pbStablish_clicked();
};

#endif // ADMINDIALOG_H
