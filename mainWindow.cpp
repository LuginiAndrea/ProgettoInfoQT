#include "mainWindow.h"
#include "ui_mainwindow.h"

#include "QCloseEvent"


void MainWindow::closeEvent(QCloseEvent *event) {


    myStuff::scrivi_dati_user(my_user);
    event->accept();
}

MainWindow::MainWindow(const QString& __cred, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("User Window");
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    my_user.credenziali = __cred;
    myStuff::carica_dati_user(my_user);
    this->setFixedSize(this->size()); //Fa in modo che la grandezza non sia modificabile
    QStringList tmp;
    myStuff::user_treno temp;
    temp._tratta = "ciao";
    temp._prima_classe.push_back(1);
    temp._prima_classe.push_back(0);
    temp._codice_treno_puntato = "C-01";

    my_user.treni_prenotati.push_back(temp);
    my_user.to_String_List(tmp);

    for (auto val : tmp)
        myStuff::messaggio("VAAAL",val);

}

MainWindow::~MainWindow()
{
    delete ui;
}


