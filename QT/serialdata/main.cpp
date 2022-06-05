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
    db.newdbandquery();
    db.lead_exceltodb();
    for (int i = 1; i < 1 + db.a; i++)
        {
            for (int j = 1; j < 1 + db.b; j++)
            {
                if(i>=2&&j==1)
                {
                qDebug()<<db.exceldata[i][j];
                if(db.exceldata[i][j]=="E3C8AB4")
                {
                    //QString Xming=db.exceldata[i][j+1];
                    qDebug()<<db.exceldata[i][2];
                }
                else if(db.exceldata[i][j]=="7CBDA38")
                {
                    QString Xming =db.exceldata[i][j+1];
                    qDebug()<<Xming;
                }
                else if(db.exceldata[i][j]=="5C88271C")
                {
                    QString Xming=db.exceldata[i][j+1];
                    qDebug()<<Xming;
                }
                }
            }
        }
    //w.Serial_read();
    //QObject::connect(&w,SIGNAL(showdatabase()),&database,SLOT(recievejump()));
    return a.exec();
}
