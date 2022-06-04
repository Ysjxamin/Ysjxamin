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
    //this->testdata();
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
    //串口读取数据
    QByteArray mytemp=serialport->readAll();
    qDebug()<<mytemp;
    //对数据进行拆分，设定通讯协议
    //读取受检人 NFC ID号
     StrI1=tr(mytemp.mid(mytemp.indexOf("I")+1,mytemp.indexOf("D")-mytemp.indexOf("I")-1));
     StrI2=tr(mytemp.mid(mytemp.indexOf("B")+1,mytemp.indexOf("H")-mytemp.indexOf("B")-1));
    qDebug()<<StrI1;
    qDebug()<<StrI2;
    //UI界面显示ID号 
    ui->lcdHuim->display(StrI2);

   // DataBase db;
   //this->testdata();

    if(StrI1=="5C88271C")
    {
        ui->labelXming->setText("杨铭");
        serialport->write("杨铭\n");
    }
    else if(StrI1=="E3C8AB4")
    {
        ui->labelXming->setText("俊荣");
        serialport->write("俊荣\n");
    }
    else if(StrI1=="7CBDA38")
    {
        ui->labelXming->setText("老六");
        serialport->write("老六\n");
    }
    //ui->labelXming->setText(StrI1);
    //ui->lcdHuim_2->display(StrI1);
    //ui->lcdXming->display(StrI1);
    //ui->lcdTemp->display(StrI2);
    /*
    QByteArray recvData;
    try {
        recvData = SerialGetData::serial_recv_Data();//从串口接收数据
    } catch (MyExcption &err) {
        QMessageBox::warning(NULL , "提示", err.what());
        return;
    }
    QString receive = QString::fromLocal8Bit(recvData.constData());
    //json格式数据解析 比如：{"温度":"10℃","湿度":"20%"}
    QJsonParseError err;
    QByteArray arr ;
    arr.append(receive);
    QJsonDocument doc = QJsonDocument::fromJson(arr,&err);
    if(err.error != QJsonParseError::NoError){
        qDebug() << "转换失败";
        return;
    }
    QJsonObject obj = doc.object();
    temp = SerialGetData::getNumsFromStr(obj.value("姓名").toString());
    humi = SerialGetData::getNumsFromStr(obj.value("编号").toString());
   // qDebug() << receive;
*/
    /*分割字符串的方法*/
    /*//自定义数据格式（温度:10-湿度:20或者10℃-20%）
    QStringList list = receive.split("-");//以:分割字符串
    if(list[0].contains("温度") || list[0].contains("℃")){
        temp = SerialGetData::getNumsFromStr(list[0]);
        humi = SerialGetData::getNumsFromStr(list[1]);
    }
    else if(list[0].contains("湿度") || list[0].contains("%")){
        temp = SerialGetData::getNumsFromStr(list[1]);
        humi = SerialGetData::getNumsFromStr(list[0]);
    }
    else{
        QMessageBox::information(NULL,"提示","数据格式错误",QMessageBox::Ok);
        return;
    }
    */

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
  this->hide();  //屏蔽交互界面
  emit showdatabase();  //发射信号，让信号传送到数据库页面

}
void SerialGetData::testdata()
{
/*
    DataBase db;
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
        */
}
