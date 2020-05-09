#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Admin Mode");
    ui->dateEdit->setMinimumDate(QDate::currentDate());
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
