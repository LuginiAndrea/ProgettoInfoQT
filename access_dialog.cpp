#include "access_dialog.h"
#include "ui_access_dialog.h"
#include "QCloseEvent"
#include "QString"
#include "QFile"
#include "QTextStream"
#include "mystuff.h"

Access_Dialog::Access_Dialog(QString* __cred, char* __from_Btn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Access_Dialog)
{
    this->setWindowTitle("Login");
    _fromButton = __from_Btn; //from Button is by default false
    *_fromButton = 0;
    ui->setupUi(this);
    credenziali = __cred;
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false); //Toglie il "?" dallo status bar
    this->setFixedSize(this->size()); //Fa in modo che la grandezza non sia modificabile
}

Access_Dialog::~Access_Dialog()
{
    delete ui;
}


void Access_Dialog::on_btn_leave_clicked()
{
    QFile file("Files/users.txt");
    QString cred = ui->lineEdit->text() + "," + ui->lineEdit_2->text();
    cred = cred.toLower();
    *credenziali = cred;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        myStuff::messaggio("ERRORE!","Errore nella apertura del file");
        exit(EXIT_FAILURE);
    }

    else {

        if (cred == ",") {
            myStuff::messaggio("ERRORE","Credenziali inserite non valide");
            *_fromButton = 3;
        }

        else {

            QTextStream stream(&file);

            if (stream.readLine() == cred) *_fromButton = 1;

            else {

                while (!stream.atEnd()) {
                    if (cred == stream.readLine()) {
                        *_fromButton = 2;
                        break;
                    }
                }
            }

            if (*_fromButton == 3)
                 myStuff::messaggio("ERRORE","Nessun account con le credenziali inserite");
        }
    }

    file.close();
    if(*_fromButton != 3)
        this->close();

    else *_fromButton = 0;

            myStuff::messaggio("chiudo","NON CHIUDO");
}



void Access_Dialog::on_btn_crea_clicked()
{
    QFile file("Files/users.txt");
    QString cred = ui->lineEdit->text() + "," + ui->lineEdit_2->text();
    cred = cred.toLower();
    bool found = false;

    if(!file.open(QIODevice::ReadOnly)) {
        myStuff::messaggio("ERRORE!","Errore nella apertura del file");
        file.close();
        exit(EXIT_FAILURE);
    }


    else {

        file.close();
        file.open(QIODevice::ReadWrite | QIODevice::Text);

        QTextStream stream(&file);

        if (cred == "," || cred == stream.readLine())
            myStuff::messaggio("ERRORE","Credenziali inserite non valide");

        else {


             while (!stream.atEnd()) {
                    if (cred == stream.readLine()) {
                        myStuff::messaggio("ERRORE!","Account con queste credenziali già esistente");
                        found = true;
                        break;
                    }
                }

            if (found == false) {
                QStringList tmp = cred.split(",");
                QFile new_file("Files/UsersData/" + tmp[0] + tmp[1] + ".txt");

                if (!new_file.open(QIODevice::WriteOnly)) {
                     myStuff::messaggio("ERRORE!","Errore nella creazione del file");
                     exit(EXIT_FAILURE);
                }

                else {
                    myStuff::messaggio("SUCCESSO!","Account creato con successo\n");
                    stream << "\n" << cred;
                }

                new_file.close();
             }
        }
    }

    file.close();
}





void Access_Dialog::on_btn_del_clicked()
{
    QFile file("Files/users.txt");
    QString cred = ui->lineEdit->text() + "," + ui->lineEdit_2->text();
    cred = cred.toLower();
    bool found = false;

    if(!file.open(QIODevice::ReadOnly)) {
        myStuff::messaggio("ERRORE!","Errore nella apertura del file");
        file.close();
        exit(EXIT_FAILURE);
    }


    else {

        file.close();

        file.open(QIODevice::ReadWrite | QIODevice::Text);

        if (cred == ",")
            myStuff::messaggio("ERRORE","Credenziali inserite non valide");

        else {

             QTextStream stream(&file);
             QString tempString;
             tempString += stream.readLine();
             QString line;



             while (!stream.atEnd()) {

                    line = stream.readLine();
                    if (cred == line)
                        found = true;

                    else
                     tempString += line + "\n";
                }

            if (found == false)
                myStuff::messaggio("ERRORE!", "Nessun account con quelle credenziali");

             else {
                file.resize(0);
                stream << tempString;
                QStringList tmp = cred.split(",");

                QFile delFile ("Files/UsersData/" + tmp[0] + tmp[1] + ".txt");
                if (!delFile.open(QIODevice::ReadOnly)) myStuff::messaggio("ERRORE!","Errore nella eliminazione del file");

                else {

                    myStuff::messaggio("SUCCESSO!", "Account cancellato");
                    delFile.remove();
               }
                delFile.close();
             }
        }
    }

    file.close();
}
