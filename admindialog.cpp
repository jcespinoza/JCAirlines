#include "admindialog.h"
#include <QMessageBox>
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
    initializeGraphics();
    doConnects();
    loadFromXML();
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::initializeGraphics()
{
    //ui->grid->addWidget(gArea);
    setToolTip("Mapa de Aeropuertos. Click para agregar uno.\nClick sobre uno para establecer una connexion.\nClick derecho sobre uno para borrarlo");
}

void AdminDialog::doConnects()
{
    ui->lePrice->setValidator(new QDoubleValidator(0.0, 9999999.99, 2,this));
    connect(gArea, SIGNAL(clickedEmpty(QPoint)), this, SLOT(requestInfo(QPoint)));
    connect(this, SIGNAL(pointApproved(QPoint)), gArea, SLOT(createPoint(QPoint)));
    connect(gArea, SIGNAL(clickedExisting(QPoint)), this, SLOT(showConnection(QPoint)));
    connect(gArea, SIGNAL(rightClickedValid(QPoint)), this, SLOT(requestDelete(QPoint)));
    connect(this, SIGNAL(deleteApproved(QPoint)), gArea, SLOT(deleteGraphicsInvolved(QPoint)));
    connect(this, SIGNAL(addLine(QPoint,QPoint)), gArea, SLOT(createLine(QPoint,QPoint)));
}

Airport AdminDialog::getFromPoint(QPoint p)
{
    Airport result;
    result.setLocation(p);
    Vertex<Airport>* t = airports->getVertex(result);
    if( t ) result = t->data;

    return result;
}

Airport AdminDialog::getFromCode(QString st)
{
    Airport result;
    result.setCode(st);
    Vertex<Airport>* t = airports->getVertex(result);
    if( t ) result = t->data;

    return result;
}

void AdminDialog::closeEvent(QCloseEvent *)
{
    saveFileToXML();
    close();
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
    if(airports->vertexExists(newOne)){
        QMessageBox::warning(this, "Error", "Ya se registro un aeropuerto con esa informacion", QMessageBox::Ok);
        return;
    }
    airports->addVertex(newOne);
    emit pointApproved(p);
    modified = true;
}

void AdminDialog::requestDelete(QPoint p)
{
    Airport target = getFromPoint(p);
    if(QMessageBox::question(this, "Borrar Aeropuerto", "Ha solicitado borrar un aeropuerto.\nTodas las conexiones con el seran borradas tambien. Esta seguro?")
            == QMessageBox::Cancel)
        return;
    airports->removeVertex(target);
    emit deleteApproved(p);
    modified = true;
}

void AdminDialog::showConnection(QPoint p)
{
    ui->originCbo->clear();
    ui->destCbo->clear();

    Airport origin = getFromPoint(p);
    QString s(origin.getCode());
    ListPointerT<Airport> allElse = airports->getAllBut(origin);

    ui->originCbo->addItem(s);
    for(int i = 0; i < allElse.getCount(); i++)
        ui->destCbo->addItem(allElse.get(i).getCode());
}

void AdminDialog::on_pbStablish_clicked()
{
    if(ui->originCbo->currentText().isEmpty() || ui->destCbo->currentText().isEmpty()){
        QMessageBox::information(this, "Instrucciones", "Seleccione un Origen haciendo click en el, elija un destino y estabelzca un precio.");
        return;
    }
    bool priceOk;
    double price = ui->lePrice->text().toDouble(&priceOk);
    if(!priceOk){
        QMessageBox::critical(this, "Error", "El precio esta en un formato invalido. Introduzca un decimal correcto.", QMessageBox::Ok);
        return;
    }

    Airport origin = getFromCode(ui->originCbo->currentText());
    Airport destination = getFromCode(ui->destCbo->currentText());
    if(origin.getLocation() == destination.getLocation()) return;
    if(airports->connectionExists(origin, destination)){
        Edge<Airport>* con = airports->getConnection(origin, destination);
        if( QMessageBox::question(this, "Conexion ya existe", "Ya existe una conexion entre estos dos aeropuertos con un costo de " + QString::number(con->value) +"\nModificar con el nuevo valor?")
               == QMessageBox::Yes){
            con->value = price;
            QMessageBox::information(this, "Completado", "Se actualizo la conexion exitosamente.");
        }
    }else{
        airports->addConnection(origin, destination, price);
        emit addLine(origin.getLocation(), destination.getLocation());
        QMessageBox::information(this, "Completado", "Se creo la conexion exitosamente");
    }
    modified = true;
    ui->originCbo->clear();
    ui->destCbo->clear();
    ui->lePrice->clear();
}

void AdminDialog::saveFileToXML()
{
    if(!modified)
        return;
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
        ListPointerT<Edge<Airport>* >  cons = airports->getVertex(a)->getAllEdges();
        for(int i = 0; i < cons.getCount(); i++){
            Edge<Airport>* e = cons.get(i);
            QDomElement connection = document.createElement("Connection");
            if(e->destin){
                connection.setAttribute("Destination", e->destin->data.getCode());
                connection.setAttribute("Cost", e->value);
                airport.appendChild(connection);
            }
        }
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
    for(int i = 0; i < airs.count(); i++){
        QDomElement node = airs.at(i).toElement();
        Airport newOne;
        newOne.setLocation(QPoint(node.attribute("X",0).toInt(), node.attribute("Y",0).toInt()));
        QDomNodeList cons = node.childNodes();
        for(int k = 0; k < cons.count(); k++){
            QDomNode nCon = cons.at(k);
            if(nCon.isElement()){
                QDomElement elCon = nCon.toElement();
                Airport temp;
                temp.setCode(elCon.attribute("Destination", "AIR00"));
                double cost = elCon.attribute("Cost", "0.0").toDouble();
                airports->addConnection(newOne,temp,cost);
                bool ok;
                temp = airports->getVertexWith(temp, ok);
                if(ok)
                    gArea->createLine(newOne.getLocation(), temp.getLocation());
            }
        }
    }
}


