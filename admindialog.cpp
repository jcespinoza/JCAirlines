#include "admindialog.h"
#include <QInputDialog>
#include "ui_admindialog.h"
#include "newairportdialog.h"

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    airports = new Graph<Airport>();
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
    connect(gArea, SIGNAL(clickedExisting(QPoint)), this, SLOT(showConnection(QPoint)));
}

Airport AdminDialog::getFromPoint(QPoint p)
{
    Airport result;
    result.setLocation(p);

    Vertex<Airport>* t = airports->getVertex(result);
    if( t )
        result = t->data;

    return result;
}

void AdminDialog::requestInfo(QPoint p)
{
    NewAirportDialog dialog(this);
    if(dialog.exec() != QDialog::Accepted)
        return;
    Airport newOne;
    newOne.setCode(dialog.getCode());
    newOne.setCity(dialog.getCity());
    newOne.setLocation(p);
    qDebug() << "Creating Airport:" << newOne.getCity() << newOne.getCode() << newOne.getLocation();

    airports->addVertex(newOne);
    airports->printVertexList();
    emit pointApproved(p);
}

void AdminDialog::showConnection(QPoint p)
{
    ui->originCbo->clear();
    ui->destCbo->clear();

    Airport origin = getFromPoint(p);
    QString s(origin.code);
    ListPointerT<Airport> allElse = airports->getAllBut(origin);

    ui->originCbo->addItem(s);
    for(int i = 0; i < allElse.getCount(); i++)
        ui->destCbo->addItem(allElse.get(i).code);
}

void AdminDialog::saveFileToXML()
{

}
