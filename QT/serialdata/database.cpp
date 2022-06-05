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
void DataBase::newdbandquery()
{
    //这种方式是一个具体的可以长期保存的数据库
    db.setDatabaseName("mysql.db");
    if(false== db.open())
    {
    QMessageBox::critical(0,"Cannot open database","Unable to establish"
                           " a database connection.",QMessageBox::Cancel);

    }
    QSqlQuery query(db);
    QString idquery="create table students(id int primary key,name text,num int)";
    query.exec(idquery);
    model=new QSqlTableModel(this);
    model->setTable("students");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
}
void DataBase::recievejump()
{
    this->show();
}
void DataBase::lead_exceltodb()
{
    QString path=QFileDialog::getOpenFileName(this,"open","../","execl(*.xlsx)");

    if(path.isEmpty()==false)
    {
        //文件对象
          QFile file(path);
          bool flag = file.open(QIODevice::ReadOnly);
          if(flag==true)
          {
        QAxObject *excel = new QAxObject(this);//建立excel操作对象
        excel->setControl("Excel.Application");//连接Excel控件
        excel->setProperty("Visible", false);//不显示窗体看效果
        excel->setProperty("DisplayAlerts", false);//不显示警告看效果
        /*********获取COM文件的一种方式************/
       QAxObject *workbooks = excel->querySubObject("WorkBooks");
       //获取工作簿(excel文件)集合
       workbooks->dynamicCall("Open(const QString&)", path);//path至关重要，获取excel文件的路径
      //打开一个excel文件
       QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
       QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);//访问excel中的工作表中第一个单元格
       QAxObject *usedRange = worksheet->querySubObject("UsedRange");//sheet的范围
       /*********获取COM文件的一种方式************/
                          //获取打开excel的起始行数和列数和总共的行数和列数
                          int intRowStart = usedRange->property("Row").toInt();//起始行数
                          int intColStart = usedRange->property("Column").toInt(); //起始列数
                          QAxObject *rows, *columns;
                          rows = usedRange->querySubObject("Rows");//行
                          columns = usedRange->querySubObject("Columns");//列
                          int intRow = rows->property("Count").toInt();//行数
                          int intCol = columns->property("Count").toInt();//列数
                          //起始行列号
                          //qDebug()<<intRowStart;
                          //qDebug()<<intColStart;
                          //行数和列数
                         // qDebug()<<intRow;
                          //qDebug()<<intCol;
                          this->a=intRow-intRowStart+1;
                          this->b=intCol-intColStart+1;
                                              QByteArray text[a][b];
                                              //QString exceldata[a][b];
                                              int coerow=0,coecol=0;
                                              for (int i = intRowStart; i < intRowStart + intRow; i++,coerow++)
                                                  {
                                                      coecol=0;//务必是要恢复初值的
                                                      for (int j = intColStart; j < intColStart + intCol; j++,coecol++)
                                                      {

                                                          QAxObject  *cell = excel->querySubObject("Cells(Int, Int)", i, j );
                                                          QVariant cellValue = cell->dynamicCall("value");
                                                          text[coerow][coecol]=cellValue.toByteArray();//QVariant转换为QByteArray
                                                           exceldata[coerow][coecol]=QString(text[coerow][coecol]);//QByteArray转换为QString
                                                          // qDebug()<<exceldata[coerow][coecol];
                                                      }
                                                  }
                                              workbook->dynamicCall( "Close(Boolean)", false );
                                              excel->dynamicCall( "Quit(void)" );
                                              delete excel;
                                              QMessageBox::warning(this,tr("读取情况"),tr("读取完成！"),QMessageBox::Yes);


    }
          file.close();

}
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
