#include "mwindow.h"
#include "ui_mwindow.h"

MWindow::MWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWindow)
{
    ui->setupUi(this);
}

MWindow::~MWindow()
{
    delete ui;
}

void MWindow::on_pushButton_clicked()
{
    AdminDialog admDialog(this);
    admDialog.exec();
}

void MWindow::on_pushButton_2_clicked()
{
    ClientDialog cliDialog(this);
    cliDialog.exec();
}
