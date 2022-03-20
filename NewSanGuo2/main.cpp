#include "mainwindow.h"
#include <QApplication>
#include"gamewindow.h"
#include"hero.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    GameWindow game;
    Hero hero;
    w.show();

    return a.exec();
}
