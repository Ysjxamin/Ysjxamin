#include "database.h"
#include "ui_database.h"
#include <QSqlDatabase>
#include <QMessageBox>

DataBase::DataBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataBase)
{
    ui->setupUi(this);

}

DataBase::~DataBase()
{
    delete ui;
}
void DataBase::create_db()
{
    //这种方式是一个具体的可以长期保存的数据库
    db.setDatabaseName("mysql.db");
    if(false== db.open())
    {
    QMessageBox::critical(0,"Cannot open database","Unable to establish"
                           " a database connection.",QMessageBox::Cancel);

    }
    QSqlQuery query(db);
    QString idquery="create table students(id text primary key,name text,num int)";
    query.exec(idquery);
    model=new QSqlTableModel(this);
    model->setTable("students");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
}

void DataBase::lead_serialtodb()
{
    int rownum=model->rowCount();//获取行数
     qDebug()<<rownum;
     model->insertRow(rownum);
     model->setData(model->index(rownum,0),_id);
     model->setData(model->index(rownum,1),_name);
     model->setData(model->index(rownum,2),(rownum+1));
     model->submitAll();
}
void DataBase::recievejump()
{
    this->show();
}

//添加
void DataBase::on_pushButton_clicked()
{
   int rownum=model->rowCount();//获取行数
    int id=3127246;
    QString name="赵猛";
    int num=1;
    qDebug()<<rownum;
    model->insertRow(rownum);
    model->setData(model->index(rownum,0),id);
    model->setData(model->index(rownum,1),name);
    model->setData(model->index(rownum,2),num);
    model->submitAll();

}
//清空表格数据
void DataBase::on_clearquery_clicked()
{
    model->setTable("students");
    model->select();
    query.prepare(clear_sql);
    if(!query.exec())
    {
    qDebug()<<query.lastError();
    }
    else
    {
    qDebug()<<"table created!";
    }
    model->submitAll();
    model->setTable("students");
    model->select();
}

void DataBase::on_lookfor_clicked()
{
    //查询
    QString name = ui->lineEdit->text();
    model->setFilter(QString("name = '%1'").arg(name));
    model->select();

}

void DataBase::on_setorder_clicked()
{
    //升序排序
    model->setSort(0,Qt::AscendingOrder);
    model->select();
}

void DataBase::on_showall_clicked()
{
    //显示全表
    model->setTable("students");
    model->select();
}
