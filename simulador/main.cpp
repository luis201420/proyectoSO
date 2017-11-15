#include <QApplication>
#include <vector>
#include <QScrollArea>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow * ventana=new MainWindow(1000,600);
    ventana->show();

    return a.exec();
}
