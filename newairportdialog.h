#ifndef NEWAIRPORTDIALOG_H
#define NEWAIRPORTDIALOG_H

#include <QDialog>

namespace Ui {
class NewAirportDialog;
}

class NewAirportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewAirportDialog(QWidget *parent = 0);
    ~NewAirportDialog();
public slots:
    void setCode(QString co){code = co;}
    void setCity(QString ci){city = ci;}

private:
    Ui::NewAirportDialog *ui;
    QString code;
    QString City;
};

#endif // NEWAIRPORTDIALOG_H
