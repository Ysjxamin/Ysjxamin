#include "serialgetdata.h"
#include "database.h"
#include <QSqlDatabase>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataBase db;
    db.create_db();
    SerialGetData w;
    w.setWindowTitle("核酸检测信息平台");//核酸检测信息平台
    w.show();
    QObject::connect(&w,SIGNAL(showdatabase()),&db,SLOT(recievejump()));
    //Qt5风格
   // QObject::connect(&w,SIGNAL(lead_todb()),&db,SLOT(lead_serialtodb()));
/*
    QObject::connect(&w,SIGNAL(lead_todb()),
            [=](QString)
    {
        //db._id=w.id;
        //db._name=w.name;
        //db._num=w.num;
        //db.lead_serialtodb();
    });
*/
    QObject::connect(&w, &SerialGetData::lead_todb,&db, [&]
    {
        int time=0;
      qDebug()<<time++;
       db._id=w.id;
       db._name=w.name;
       db._num=w.num;
       db.lead_serialtodb();
       //显示全表
       db.model->setTable("students");
       db.model->select();
    });
    //while(1)
    //{
       //db._id=w.id;
       //db._name=w.name;
       //db._num=w.num;
       // db.lead_serialtodb();
    //}
    return a.exec();
}
