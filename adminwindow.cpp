#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin Mode");
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    this->setFixedSize(this->size()); //Fa in modo che la grandezza non sia modificabile
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
