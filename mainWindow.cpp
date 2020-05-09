#include "mainWindow.h"
#include "ui_mainwindow.h"
#include "QCloseEvent"

MainWindow::MainWindow(const QString& __cred, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("User Window");
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    my_user.credenziali = __cred;
    myStuff::carica_dati_user(my_user);
    myStuff::carica_treni_vector(vettore_treni);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    myStuff::scrivi_dati_user(my_user); //Alla chiusura del programma scriviamo i dati
    myStuff::scrivi_treni_vector(vettore_treni);
    event->accept();
}
