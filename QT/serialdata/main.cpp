#include "serialgetdata.h"
#include "database.h"
#include <QSqlDatabase>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataBase db;
    SerialGetData w;
    w.setWindowTitle("核酸检测信息平台");//核酸检测信息平台
    w.show();
    QObject::connect(&w,SIGNAL(showdatabase()),&db,SLOT(recievejump()));
    return a.exec();
}
