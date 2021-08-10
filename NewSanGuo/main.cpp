#include "mainwindow.h"
#include <QApplication>
#include"gamewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameWindow game;
    w.show();

    return a.exec();
}
