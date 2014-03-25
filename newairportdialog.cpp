#include "newairportdialog.h"
#include "ui_newairportdialog.h"
#include <QMessageBox>

NewAirportDialog::NewAirportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewAirportDialog)
{
    ui->setupUi(this);
    connect(ui->leCode, SIGNAL(textChanged(QString)), this, SLOT(setCode(QString)));
    connect(ui->leCity, SIGNAL(textChanged(QString)), this, SLOT(setCity(QString)));
    ui->leCode->setFocus();

    ui->leCode->setValidator(new QRegExpValidator(QRegExp("[A-Z]{2}\\d{2}"),this));
}

NewAirportDialog::~NewAirportDialog()
{
    delete ui;
}

void NewAirportDialog::on_buttonBox_accepted()
{
    if(ui->leCity->text().isEmpty() || ui->leCode->text().isEmpty()){
        setResult(QDialog::Rejected);
        QMessageBox::critical(this, "Datos Invalidos", "No se permite dejar ningun campo vacio.");
    }
}
