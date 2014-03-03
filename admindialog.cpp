#include "admindialog.h"
#include "ui_admindialog.h"

AdminDialog::AdminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDialog)
{
    ui->setupUi(this);
    gArea = new GraphicArea(this);
    gArea->setGeometry(ui->gridWidget->geometry());
}

AdminDialog::~AdminDialog()
{
    delete ui;
}

void AdminDialog::initializeGraphics()
{
    ui->grid->addWidget(gArea);
}
