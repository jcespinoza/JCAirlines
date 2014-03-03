#ifndef MWINDOW_H
#define MWINDOW_H

#include <QMainWindow>
#include "admindialog.h"

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

private:
    Ui::MWindow *ui;
    AdminDialog *admDialog;
};

#endif // MWINDOW_H
