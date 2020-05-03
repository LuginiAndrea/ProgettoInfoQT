#include "access_dialog.h"
#include "ui_access_dialog.h"
#include "QCloseEvent"
#include "QString"
#include "QFile"
#include "QTextStream"
#include "mystuff.h"

Access_Dialog::Access_Dialog( char* __from_Btn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Access_Dialog)
{
    this->setWindowTitle("Login");
    Access_Dialog::_fromButton = __from_Btn; //from Button is by default false
    *_fromButton = 0;
    ui->setupUi(this);
}

Access_Dialog::~Access_Dialog()
{
    delete ui;
}


void Access_Dialog::on_btn_leave_clicked()
{
    QFile file("users.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);


    //Inserire controlli per username e password
    /*if (controllo)*/ *_fromButton = 2; //we say to the class that we are calling the close event from the button
    this->close();
}
