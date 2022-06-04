#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlError>
#include <QFileDialog>
#include <QAxObject>
#include "serialgetdata.h"
namespace Ui {
class DataBase;
}

class DataBase : public QWidget
{
    Q_OBJECT

public:
    explicit DataBase(QWidget *parent = nullptr);
    friend class SerialGetData;
    ~DataBase();
private slots:
    void recievejump(); //接受跳转信号槽函数
    void on_pushButton_clicked();

    void on_clearquery_clicked();

    void on_lookfor_clicked();

    void on_setorder_clicked();

    void on_showall_clicked();

private:
    Ui::DataBase *ui;

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");

    QSqlTableModel *model;

    QSqlQuery query;

    QString insert_sql = "insert into student values (?, ?, ?)";

    QString clear_sql = "delete from students";

    QVector<QString> arr;	//存储每一行数据

    QVector<QVector<QString>> array;	//将每行数据汇总，类似于二维数组，但不需要手动定义空间大小，造成内存浪费
public:
    int a,b;
    QString exceldata[6][6];
        void lead_exceltodb();
      //  DataBase* database;

};

#endif // DATABASE_H
