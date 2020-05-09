#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mystuff.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString& cred, QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent *event); //Override  della funzione

private slots:


private:
    Ui::MainWindow *ui;
    myStuff::User my_user;
    QVector <myStuff::Treno> vettore_treni;
};
#endif // MAINWINDOW_H
