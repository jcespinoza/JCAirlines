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
    loadXml();
}

void ClientDialog::loadXml()
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
