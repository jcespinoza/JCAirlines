#include "clientdialog.h"
#include "ui_clientdialog.h"
#include <QtXml>

ClientDialog::ClientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientDialog)
{
    ui->setupUi(this);   
    initAndConnect();
}

ClientDialog::~ClientDialog()
{
    delete ui;
}

void ClientDialog::closeEvent(QCloseEvent *)
{
    close();
}

void ClientDialog::initAndConnect()
{
    xmlPath = "../Airline.xml";
    gArea = new GraphicArea(this);
    airports = new Graph<Airport>();
    gArea->setGeometry(ui->gridWidget->geometry());
    //setToolTip("Mapa de Aeropuertos.");
    loadXml();
    loadAirportsOnCombos();
    connect(ui->cboOrigin, SIGNAL(currentIndexChanged(int)), gArea, SLOT(resetGraphics(int)));
    connect(ui->cboDestin, SIGNAL(currentIndexChanged(int)), gArea, SLOT(resetGraphics(int)));
    connect(this, SIGNAL(resetGraphics(int)), gArea, SLOT(resetGraphics(int)));
}


void ClientDialog::on_pbCalculate_clicked()
{
    emit resetGraphics(0);
    int fromIndex = ui->cboOrigin->currentIndex(), toIndex = ui->cboDestin->currentIndex();
    Vertex<Airport>* from = airports->getVertex(fromIndex);
    Vertex<Airport>* dest = airports->getVertex(toIndex);
    QString mes;
    if(fromIndex == toIndex || !from || !dest){
        mes = QString("El costo para llegar a este punto es de 0.0, es mas ni siquiera tiene que moverse. ;)");
    }else{
        ListPointerT< Vertex<Airport>* > path = airports->getLowesCostPath(from, dest);
        if(path.getCount() > 0){
            mes = extractFullMessage(path);
        }else
            mes = QString("No hay manera de llegar a " + dest->data.getCity() + " partiendo de " + from->data.getCity());
    }
    ui->lbResult->setText(mes);
}

void ClientDialog::resetAll(int)
{
    ui->lbResult->setText("");
    emit resetGraphics(0);
}

void ClientDialog::loadXml()
{
    QDomDocument document;
    QFile file(xmlPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Failed to Read the file";
        return;
    }else{
        if(!document.setContent(&file)){
            qDebug() << "Failed to load the document";
            file.close();
            return;
        }
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

void ClientDialog::loadAirportsOnCombos()
{
    ui->cboOrigin->clear();
    ui->cboDestin->clear();
    ListPointerT<Airport> elem = airports->getAllVertices();
    for(int i = 0; i < elem.getCount(); i++){
        QString city = elem.get(i).getCity();
        ui->cboOrigin->addItem(city);
        ui->cboDestin->addItem(city);
    }
}

QString ClientDialog::extractFullMessage(ListPointerT<Vertex<Airport> *> path)
{
    double totalCost = 0;
    QString result("El costo total por este viaje es de $");
    QString route(" siguiendo la ruta:\n");
    for(int i = 0; i < path.getCount(); i++){
        Vertex<Airport>* current = path.get(i);
        gArea->highlightPoint(current->data.getLocation(),QPoint());
        Vertex<Airport>* next = path.get(i+1);
        if(next){
            Edge<Airport>* edge = current->getEdge(next);
            gArea->highlightEdge(current->data.getLocation(), next->data.getLocation());
            if(edge)
                totalCost += edge->value;
        }
        if(current)
            route += (current->data.getCity()) +  ((i < path.getCount()-1)?" - ":".");
    }
    result += QString::number(totalCost);
    result += route;
    gArea->update();
    return result;
}
