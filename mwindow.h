#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include "admindialog.h"
#include "clientdialog.h"

namespace Ui {
class MWindow;
}

class MWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MWindow(QWidget *parent = 0);
    ~MWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MWindow *ui;
};

#endif // MWINDOW_H
