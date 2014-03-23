#include "admindialog.h"
#include <QtXml>
#include <QInputDialog>
#include "ui_admindialog.h"
#include "newairportdialog.h"

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    xmlPath = "../Airline.xml";
    airports = new Graph<Airport>();
    gArea = new GraphicArea(this);
    gArea->setGeometry(ui->gridWidget->geometry());
    doConnects();
    loadFromXML();
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
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(saveFileToXML()));
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
    QDomDocument document;
    QDomProcessingInstruction xmlHeader = document.createProcessingInstruction("xml","version=\"1.0\"");
    document.appendChild(xmlHeader);
    QDomElement airportsList = document.createElement("Airports");

    document.appendChild(airportsList);

    ListPointerT<Airport> list = airports->getAllVertices();
    for(int i = 0; i < list.getCount(); i++){
        Airport a = list.get(i);
        QDomElement airport = document.createElement("Airport");
        airport.setAttribute("X", a.getLocation().x());
        airport.setAttribute("Y", a.getLocation().y());
        airport.setAttribute("Code", a.getCode());
        airport.setAttribute("City", a.getCity());
        airportsList.appendChild(airport);
    }

    qDebug() << document.toString();

    QFile file(xmlPath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug() << "Something went wrong while opening the file";
    else{
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
    }
}

void AdminDialog::loadFromXML()
{
    QDomDocument document;
    QFile file(xmlPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Failed to Read the file";
        return;
    }else{
        if(!document.setContent(&file))
            qDebug() << "Failed to load the document";
        file.close();
    }

    QDomElement root = document.firstChildElement();
    QDomNodeList airs = root.elementsByTagName("Airport");
    for(int i = 0; i < airs.count(); i++){
        QDomNode node = airs.at(i);
        if(node.isElement()){
            QDomElement elem = node.toElement();
            Airport newOne;
            newOne.setCode(elem.attribute("Code", "AIR00"));
            newOne.setCity(elem.attribute("City", "City"));
            newOne.setLocation(QPoint(elem.attribute("X", 0).toInt(), elem.attribute("Y", 0).toInt()));
            airports->addVertex(newOne);
            gArea->createPoint(newOne.getLocation());
        }
    }
}
