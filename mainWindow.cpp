#include "mainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("User Window");
    ui->dateEdit->setMinimumDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
    delete ui;
}


