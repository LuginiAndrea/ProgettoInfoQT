#ifndef ACCESS_DIALOG_H
#define ACCESS_DIALOG_H

#include <QDialog>

//_fromButton e' 0 se non chiudiamo con bottone, 1 se dati admin, 2 se dati user

namespace Ui {
class Access_Dialog;
}

class Access_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Access_Dialog( char* __from_btn, QWidget *parent = nullptr);
    ~Access_Dialog();

private slots:
    void on_btn_leave_clicked();

private:
    Ui::Access_Dialog *ui;
    char* _fromButton; //Una variabile bool che usiamo per dire che possiamo effettivamente chiudere la dialog se username e password sono corretti
};

#endif // ACCESS_DIALOG_H
