#include "mainWindow.h"
#include "access_dialog.h"
#include "adminwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    char correct_close = 0;
    QString credenziali;
    Access_Dialog p(&credenziali, &correct_close);
    p.exec();

    if (correct_close == 0) {
        return  0;
    }

    MainWindow* w;
    AdminWindow* admin;

   if (correct_close == 1) {
       admin = new AdminWindow;
       admin->show();
   }

   else {
       w = new MainWindow(credenziali);
       w->show();
   }

    return a.exec();
}
