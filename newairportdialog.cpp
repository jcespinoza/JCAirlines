#include "newairportdialog.h"
#include "ui_newairportdialog.h"

NewAirportDialog::NewAirportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAirportDialog)
{
    ui->setupUi(this);
    connect(ui->leCode, SIGNAL(textChanged(QString)), this, SLOT(setCode(QString)));
    connect(ui->leCity, SIGNAL(textChanged(QString)), this, SLOT(setCity(QString)));
}

NewAirportDialog::~NewAirportDialog()
{
    delete ui;
}
