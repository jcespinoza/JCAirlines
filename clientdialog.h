#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>
#include "../GrafoTest/Grafo.h"
#include <QDebug>
#include "airport.h"
#include "graphicarea.h"

namespace Ui {
class ClientDialog;
}

class ClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientDialog(QWidget *parent = 0);
    ~ClientDialog();

private:
    Ui::ClientDialog *ui;
    Graph<Airport>* airports;
    GraphicArea* gArea;
    QString xmlPath;
    void closeEvent(QCloseEvent*);

    void initAndConnect();
    void loadXml();

};

#endif // CLIENTDIALOG_H
