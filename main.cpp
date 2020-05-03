#include "mainWindow.h"
#include "access_dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    char correct_close = 0;
    MainWindow w;
    Access_Dialog p(&correct_close);
    p.exec();
    if (!correct_close) return 0;
    w.show();
    return a.exec();
}
