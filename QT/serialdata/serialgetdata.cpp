#include "serialgetdata.h"
#include "ui_serialgetdata.h"
#include <QDebug>
#include <QMessageBox>
#include <QFontDialog>

#include <QJsonObject>
#include <QJsonDocument>
#include "database.h"
SerialGetData::SerialGetData(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SerialGetData)
{
    ui->setupUi(this); 
    //DataBase db;
    serialflag = 0;//表示串口关闭
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);// 禁止最大化按钮
    serialport = new QSerialPort();//分配内存
    ui->dateTimeEdit->setDisabled(true);//
    timerid = startTimer(1000);//开启定时器，每隔1秒
    this->read();
    this->Serial_read();

}

SerialGetData::~SerialGetData()
{
    killTimer(timerid);//关闭
    delete ui;
    delete serialport;
}

//串口获取
void SerialGetData::Serial_read()
{

    QString StrI1,StrI2;
   // QString buf;
    //串口读取数据
    mytemp=serialport->readAll();
    QString a1;
    //a1.append(buf.mid(0,5));
    if(!mytemp.isEmpty())
    {
       buf.append(tr(mytemp));
    }
    else
    {
         qDebug()<<"over";
    }
    //a1="hello";
    //buf="world";
    //a1.append(buf);
    qDebug()<<mytemp;
    qDebug()<<buf;
    //qDebug()<<a1;
    //对数据进行拆分，设定通讯协议
    //读取受检人 NFC ID号
     StrI1=buf.mid(buf.indexOf("I")+1,buf.indexOf("D")-buf.indexOf("I")-1);
     StrI2=buf.mid(buf.indexOf("Q")+1,buf.indexOf("S")-buf.indexOf("Q")-1);
     if(buf.length()>200)
     {
         buf.clear();
     }
//char message=StrI1.at(0).unicode();
 // qDebug("%s",ptr1);
  qDebug()<<times++;
   qDebug()<<StrI1;
    //  qDebug()<<StrI2;
    //UI界面显示ID号 

    ui->lcdHuim->display(StrI2);
    qDebug()<<StrI2;
    //ui->labelBhao->setText(StrI1);

    for (int i = 1; i < 1 + a; i++)
        {
            for (int j = 1; j < 1 + b; j++)
            {
                if(i>=2&&j==1)
                {

                qDebug()<<exceldata[i][j];
                if(exceldata[i][j]==StrI1)
                {
                    QString Xming=exceldata[i][j+1];
                     ui->labelXming->setText(Xming);
                    qDebug()<<exceldata[i][2];
                     ui->labelBhao->setText(exceldata[i][1]);

                  //DataBase database;
                    if(exceldata[i][5]=='0')
                    {

                        this->time++;
                        this->id=StrI1;
                        this->name=Xming;
                        //this->num=StrI2;
                        emit lead_todb();

                        exceldata[i][5]='1';

                    }

                 //database._name=Xming;
                 //database._id=StrI1;
                 //database._num=StrI2;
                // database.lead_serialtodb();
                    //this->name=Xming;

                }

                }
            }
        }

}
//串口接收
QByteArray SerialGetData::serial_recv_Data() throw(MyExcption)
{
    //读取串口收到的数据
    QByteArray buffer = serialport->readAll();
    //为空的话
    if(buffer.isEmpty()){
        throw("收到数据为空");
        return NULL;
    }
    return buffer;
}
//获取字符串中数字部分
int SerialGetData::getNumsFromStr(QString data)
{
    QString num;
    int j = 0;
    for(int i = 0 ; i < data.length();i++){
        if(data[i] >= '0' && data[i] <= '9'){
            num[j] = data[i];
            j++;
        }
    }
    return num.toInt();
}
//扫描串口
void SerialGetData::on_scanSerialBtn_clicked()
{
    // 清除当前显示的端口号
     ui->serialPortBox->clear();
     //检索端口号
     foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
     {
         ui->serialPortBox->addItem(info.portName());
     }
}
//打开串口
void SerialGetData::on_openSerialBtn_clicked()
{
    if(ui->openSerialBtn->text() == QString("打开串口"))  //串口未打开
    {
        //设置端口号
        //qDebug() << ui->serialPortBox->currentText();
        serialport->setPortName(ui->serialPortBox->currentText());
        //设置波特率
        serialport->setBaudRate(ui->baudRateBox->currentText().toInt());
        //设置数据位
        switch (ui->dataBitBox->currentText().toInt())
        {
            case 8: serialport->setDataBits(QSerialPort::Data8); break;
            case 7: serialport->setDataBits(QSerialPort::Data7); break;
            case 6: serialport->setDataBits(QSerialPort::Data6); break;
            case 5: serialport->setDataBits(QSerialPort::Data5); break;
            default: break;
        }
        //设置停止位
        switch (ui->stopBitBox->currentText().toInt())
        {
            case 1: serialport->setStopBits(QSerialPort::OneStop);break;
            case 2: serialport->setStopBits(QSerialPort::TwoStop);break;
            default:break;
        }
        //设置校验方式
        switch (ui->chekBitBox->currentIndex())
        {
            case 0: serialport->setParity(QSerialPort::NoParity);break;
            default:break;
        }
        //设置流控制模式
        serialport->setFlowControl(QSerialPort::NoFlowControl);
        //打开串口
        if(serialport->open(QIODevice::ReadWrite)==false)
        {
            QMessageBox::warning(NULL , "提示", "串口打开失败！");
            return;
        }
        // 失能串口设置控件
        ui->serialPortBox->setEnabled(false);
        ui->chekBitBox->setEnabled(false);
        ui->baudRateBox->setEnabled(false);
        ui->dataBitBox->setEnabled(false);
        ui->stopBitBox->setEnabled(false);
        ui->scanSerialBtn->setEnabled(false);
        //调整串口控制按钮的文字提示
        ui->openSerialBtn->setText(QString("关闭串口"));
        ui->openSerialBtn->setStyleSheet("background-color: rgb(255, 255, 255);\
                                       color: rgb(255,0,0);\
                                       border-color: rgb(255, 0, 0);");
        serialflag = 1;//串口打开
    }
    else       //串口已经打开
    {
        serialport->close();
        // 使能串口设置控件
        ui->serialPortBox->setEnabled(true);
        ui->chekBitBox->setEnabled(true);
        ui->baudRateBox->setEnabled(true);
        ui->dataBitBox->setEnabled(true);
        ui->stopBitBox->setEnabled(true);
        ui->scanSerialBtn->setEnabled(true);
        //调整串口控制按钮的文字提示
        ui->openSerialBtn->setText(QString("打开串口"));
        ui->openSerialBtn->setStyleSheet("background-color: rgb(0, 255, 255);\
                                       color: rgb(0,0,255);\
                                       border-color: rgb(255, 0, 0);");
        serialflag = 0;//串口关闭
    }
}
//建立连接
void SerialGetData::on_eConnectBtn_clicked()
{
   if(serialflag == 0){
       QMessageBox::information(NULL,"提示","串口未打开",QMessageBox::Ok);
       return;
   }
   ui->eConnectBtn->setEnabled(false);
   ui->eDisconnectBtn->setEnabled(true);
   ui->eConnectBtn->setStyleSheet("background-color: rgb(255, 255, 255);\
                                  color: rgb(255, 0, 0);\
                                  border-color: rgb(255, 0, 0);");
   ui->eDisconnectBtn->setStyleSheet("background-color: rgb(0, 255, 255);\
                                  color: rgb(0, 0, 255);\
                                  border-color: rgb(255, 0, 0);");
   /*
   if(connectflag == 1){
       QMessageBox::information(NULL,"提示","已建立连接",QMessageBox::Ok);
       return;
   }*/
   connect(serialport,&QSerialPort::readyRead,this,&SerialGetData::Serial_read);
   //connectflag = 1;//已为信号绑定槽函数
}
//关闭连接
void SerialGetData::on_eDisconnectBtn_clicked()
{
    if(serialflag == 0){
        QMessageBox::information(NULL,"提示","串口未打开",QMessageBox::Ok);
        return;
    }
    ui->eDisconnectBtn->setEnabled(false);
    ui->eConnectBtn->setEnabled(true);
    ui->eConnectBtn->setStyleSheet("background-color: rgb(0, 255, 255);\
                                   color: rgb(0, 0, 255);\
                                   border-color: rgb(255, 0, 0);");
    ui->eDisconnectBtn->setStyleSheet("background-color: rgb(255, 255, 255);\
                                   color: rgb(255, 0, 0);\
                                   border-color: rgb(255, 0, 0);");
    /*
    if(connectflag == 0){
        QMessageBox::information(NULL,"提示","未建立连接",QMessageBox::Ok);
        return;
    }*/
    disconnect(serialport,&QSerialPort::readyRead,this,&SerialGetData::Serial_read);
    //connectflag = 0;//已解除绑定
    //ui->lcdTemp->display(0);
    ui->lcdHuim->display(0);
}
//定时器，定时获取时间展示
void SerialGetData::timerEvent(QTimerEvent *event)
{
    //获取当前时间
    QDate currentdate = dateTime.currentDateTime().date();
    QTime currenttime = dateTime.currentDateTime().time();
    if(event->timerId() == timerid){
        ui->dateTimeEdit->setDate(currentdate);
        ui->dateTimeEdit->setTime(currenttime);
    }
}

void SerialGetData::on_eDisconnectBtn_2_clicked()
{
 // this->hide();  //屏蔽交互界面
  emit showdatabase();  //发射信号，让信号传送到数据库页面

 // emit lead_todb();

}
void SerialGetData::read()
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
                                                              qDebug()<<exceldata[coerow][coecol];
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
