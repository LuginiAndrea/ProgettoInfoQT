#include "mainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString& __cred, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("User Window");
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    my_user.credenziali = __cred;
    myStuff::carica_dati_user(my_user);
}

MainWindow::~MainWindow()
{
    delete ui;
}


