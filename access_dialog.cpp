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
    QFile file("Files/users.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&file);
    if (file.size() == 0) stream << "admin,admin\n"; //Se il file non esiste lo creo e ci scrivo le credenziali iniziali dell'admin
    file.close();

    QFile treniFile("Files/treni.txt");
    treniFile.open(QIODevice::Append); //Lo crea se non c'è
    treniFile.close();


    this->setWindowTitle("Login");
    Access_Dialog::_fromButton = __from_Btn; //from Button is by default false
    *_fromButton = 0;
    ui->setupUi(this);
    credenziali = __cred;

    this->setFixedSize(this->size());


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
    *_fromButton = 3;
    *credenziali = cred;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        myStuff::messaggio("ERRORE!","Errore nella apertura del file");
        exit(EXIT_FAILURE);
    }

    else {

        if (cred == ",")
            myStuff::messaggio("ERRORE","Credenziali inserite non valide");

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

    if (*_fromButton != 3)
        this->close();

    else *_fromButton = 0;
}



void Access_Dialog::on_btn_crea_clicked()
{
    QFile file("Files/users.txt");
    QString cred = ui->lineEdit->text() + "," + ui->lineEdit_2->text();
    cred = cred.toLower();


    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        myStuff::messaggio("ERRORE!","Errore nella apertura del file");
        exit(EXIT_FAILURE);
    }

    if (cred == ",")
        myStuff::messaggio("ERRORE","Credenziali inserite non valide");

    else {
           QTextStream stream(&file);
           QStringList tmp = cred.split(",");
            while (!stream.atEnd()) {
                    if (tmp[0] == stream.readLine().split(",")[0]) { //Non posso avere stesso username
                        myStuff::messaggio("ERRORE!","Nome utente già esistente");
                        return;
                    }
                }

                QFile new_file("Files/UsersData/U-" + tmp[0] + "P-"+tmp[1] + ".txt");

                if (!new_file.open(QIODevice::WriteOnly)) {
                     myStuff::messaggio("ERRORE!","Errore nella creazione del file"); //Creo un file dove memorizzo le info dell'utente
                     exit(EXIT_FAILURE);
                }

                else {
                    myStuff::messaggio("SUCCESSO!","Account creato con successo\n");
                    stream << cred <<"\n";
                }

                new_file.close();
             }

    file.close();
}





void Access_Dialog::on_btn_del_clicked()
{
    QFile file("Files/users.txt");
    QString cred = ui->lineEdit->text() + "," + ui->lineEdit_2->text();
    cred = cred.toLower();
    bool found = false;

        file.close();

        if(!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            myStuff::messaggio("ERRORE!","Errore nella apertura del file");
            exit(EXIT_FAILURE);
        }

        if (cred == ",")
            myStuff::messaggio("ERRORE","Credenziali inserite non valide");

        else {

             QTextStream stream(&file);
             QString tempString;
             tempString += stream.readLine();
             QString line;
             QStringList tmp = cred.split(",");

             tempString +="\n";


             while (!stream.atEnd()) {

                    line = stream.readLine();
                    if (tmp[0] == line.split(",")[0])
                        found = true;

                    else
                     tempString += line + "\n";
                }

            if (found == false)
                myStuff::messaggio("ERRORE!", "Nessun account con quelle credenziali");

             else {
                file.resize(0);
                stream << tempString;
                QFile delFile ("Files/UsersData/U-" + tmp[0] + "P-" +tmp[1] + ".txt");
                if (!delFile.open(QIODevice::ReadOnly)) myStuff::messaggio("ERRORE!","Errore nella eliminazione del file");

                else {

                    myStuff::messaggio("SUCCESSO!", "Account cancellato");
                    delFile.remove();
               }
                delFile.close();
             }
        }


    file.close();
}
