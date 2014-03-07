#include "admindialog.h"
#include <QInputDialog>
#include "ui_admindialog.h"
#include "newairportdialog.h"

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    airports = new Grafo<Airport>();
    gArea = new GraphicArea(this);
    gArea->setGeometry(ui->gridWidget->geometry());
    doConnects();
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::initializeGraphics()
{
    ui->grid->addWidget(gArea);
}

void AdminDialog::doConnects()
{
    connect(gArea, SIGNAL(clickedEmpty(QPoint)), this, SLOT(requestInfo(QPoint)));
    connect(this, SIGNAL(pointApproved(QPoint)), gArea, SLOT(createPoint(QPoint)));
}

Airport AdminDialog::getFromPoint(QPoint)
{
    Airport result;
}

void AdminDialog::requestInfo(QPoint p)
{
    NewAirportDialog dialog(this);

    if(dialog.exec() != QDialog::Accepted)
        return;
    Airport newOne;
    newOne.setCode(code);
    newOne.setLocation(p);
    Vertice<Airport>* vert = new Vertice<Airport>();
    vert->valor = newOne;
    airports->agregarVertice(vert);
    emit pointApproved(p);
}



void AdminDialog::showConnection(QPoint p)
{
    ui->originCbo->clear();
    ui->originCbo->addItem(getFromPoint(p)).;
}

void AdminDialog::saveFileToXML()
{

}
