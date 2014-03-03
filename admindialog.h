#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "graphicarea.h"

namespace Ui {
class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = 0);
    ~AdminDialog();

private:
    Ui::AdminDialog *ui;
    void initializeGraphics();
    GraphicArea *gArea;
};

#endif // ADMINDIALOG_H
