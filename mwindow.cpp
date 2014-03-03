#include "mwindow.h"
#include "ui_mwindow.h"

MWindow::MWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MWindow)
{
    ui->setupUi(this);
    admDialog = new AdminDialog(this);
}

MWindow::~MWindow()
{
    delete ui;
}

void MWindow::on_pushButton_clicked()
{
    admDialog->show();
}
