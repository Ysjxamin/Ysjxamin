#include "serialgetdata.h"
#include "database.h"
#include <QSqlDatabase>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataBase database;
    database.lead_exceltodb();
    SerialGetData w;
    //w.a=database.a;w.b=database.b;
    w.setWindowTitle("核酸检测信息平台");//核酸检测信息平台
    w.show();
    w.testdata();
    //w.Serial_read();
    QObject::connect(&w,SIGNAL(showdatabase()),&database,SLOT(recievejump()));
    return a.exec();
}
