#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QList>
#include <QDebug>
#include <QTextEdit>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);


    mSerialPort = new QSerialPort; //创建一个串口对象

    mIsOpen = false; //初始化按钮状态标志位

    flag_red = false;
    flag_yellow = false;
    flag_bee = false;

    ui->btn_send->setEnabled(mIsOpen);

    //识别系统的所有可用串口号，并添加到下拉列表中
    QList<QSerialPortInfo> serialPortInfo = QSerialPortInfo::availablePorts();
    int count = serialPortInfo.count();
    for(int i = 0;i < count;i++)
    {
        ui->Cboxport->addItem(serialPortInfo.at(i).portName());
    }

    //等待一个触发信号，接收串口数据
    connect(mSerialPort, SIGNAL(readyRead()), this, SLOT(on_SerialPort_readyRead()));
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::getSerialPortConfig()  //配置串口
{
    //获取串口配置
    mPortName = ui->Cboxport->currentText();
    mBaudRate = ui->Cboxboudrate->currentText();
    mParity = ui->Cboxparity->currentText();
    mDataBits = ui->Cboxdatabits->currentText();
    mStopBits = ui->Cboxstopbits->currentText();

    //设置串口
    //串口号
    mSerialPort->setPortName(mPortName);
    //波特率
    if("115200" == mBaudRate)
    {
        mSerialPort->setBaudRate(QSerialPort::Baud115200);
    }
    else
    {
        mSerialPort->setBaudRate(QSerialPort::Baud9600);
    }
    //校验位
    if("EVEN" == mParity)
    {
        mSerialPort->setParity(QSerialPort::EvenParity);
    }
    else if("ODD" == mParity)
    {
        mSerialPort->setParity(QSerialPort::OddParity);
    }
    else
    {
        mSerialPort->setParity(QSerialPort::NoParity);
    }
    //数据位
    if("5" == mDataBits)
    {
        mSerialPort->setDataBits(QSerialPort::Data5);
    }
    else if("6" == mDataBits)
    {
        mSerialPort->setDataBits(QSerialPort::Data6);
    }
    else if("7" == mDataBits)
    {
        mSerialPort->setDataBits(QSerialPort::Data7);
    }
    else
    {
        mSerialPort->setDataBits(QSerialPort::Data8);
    }
    //停止位
    if("1.5" == mStopBits)
    {
        mSerialPort->setStopBits(QSerialPort::OneAndHalfStop);
    }
    if("2" == mStopBits)
    {
        mSerialPort->setStopBits(QSerialPort::TwoStop);
    }
    else
    {
        mSerialPort->setStopBits(QSerialPort::OneStop);
    }
    qDebug() << "配置";
    return mSerialPort->open(QSerialPort::ReadWrite);

}
void Dialog::on_btn_open_clicked()  //打开关闭按钮状态
{
    if(true == mIsOpen)
    {
        //当前已经打开了串口，点击后将按钮更新为关闭状态
        mSerialPort->close();
        ui->btn_open->setText("打开");
        mIsOpen = false;
        //此时可以配置串口
        ui->Cboxport->setEnabled(true);
        ui->Cboxboudrate->setEnabled(true);
        ui->Cboxparity->setEnabled(true);
        ui->Cboxdatabits->setEnabled(true);
        ui->Cboxstopbits->setEnabled(true);
        ui->btn_send->setEnabled(mIsOpen);
        qDebug() << "关闭";
    }
    else
    {
        //当前处于关闭串口状态，打开前需要配置串口
        //getSerialPortConfig();
        if(true == getSerialPortConfig())
        {
            mIsOpen = true;
            ui->btn_open->setText("关闭");
            qDebug() << "成功打开串口" << mPortName;
            ui->Cboxport->setEnabled(false);
            ui->Cboxboudrate->setEnabled(false);
            ui->Cboxparity->setEnabled(false);
            ui->Cboxdatabits->setEnabled(false);
            ui->Cboxstopbits->setEnabled(false);
            ui->btn_send->setEnabled(mIsOpen);
        }
//        else
//        {
//            mIsOpen = false;
//        }
    }
}

void Dialog::on_btn_send_clicked() //发送按钮
{
    if(true == mIsOpen)
    {
        //mSerialPort->write(ui->textEdit_send->toPlainText().toLatin1());// toPlainText(将文本编辑的文本转换为纯文本)
        //mSerialPort->write(ui->textEdit_send->toPlainText().toStdString().c_str());
        //注意：write函数的传递参数是QString，先转换为C++标准的string，再转为char型
        QString str = ui->textEdit_send->toPlainText();
        int len = str.length();
        if(len%2 == 1)
        {
            str = str.insert(len - 1, '0');
        }
        QByteArray senddata;  //写入编辑框的数据
        StringToHex(str,senddata);

        int length = senddata.length();  //在帧尾追加STM32的关键帧
        senddata[length + 1] = 0x0d;
        senddata[length + 2] = 0x0a;
        mSerialPort->write(senddata);
    }
}

void Dialog::on_SerialPort_readyRead()  //读取串口数据
{
    if(true == mIsOpen)
    {
        QByteArray recvData = mSerialPort->readAll();
        //ui->textEdit_Recv->setPlainText(QString(recvData)); //显示内容每次会被覆盖
        ui->textEdit_Recv->append(QString(recvData));
        qDebug() << "正在接收数据";
    }
}

void Dialog::StringToHex(QString str, QByteArray &senddata) //字符串转换为十六进制数据0-F
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    senddata.resize(len/2);
    char lstr,hstr;

    for(int i=0; i<len; )
    {
        //char lstr,
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
}

char Dialog::ConvertHexChar(char ch)
{
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return ch-ch;//不在0-f范围内的会发送成0
}




void Dialog::on_btn_yellow_clicked()
{
    QByteArray btn_data;
    btn_data[0] = 0x01;
    btn_data[1] = 0x0d;
    btn_data[2] = 0x0a;
    mSerialPort->write(btn_data);
    if(false == flag_yellow)
     {
        ui->btn_yellow->setText("关闭");
            flag_yellow = true;
     }
     else
     {
        ui->btn_yellow->setText("打开");
            flag_yellow = false;
     }
}

void Dialog::on_btn_red_clicked()
{
    QByteArray btn_data;
    btn_data[0] = 0x00;
    btn_data[1] = 0x0d;
    btn_data[2] = 0x0a;
    mSerialPort->write(btn_data);
    if(flag_red == false)
     {
        ui->btn_red->setText("关闭");
            flag_red = true;
     }
    else
     {
        ui->btn_red->setText("打开");
            flag_red = false;
     }
}

void Dialog::on_btn_bee_clicked()
{
    QByteArray btn_data1;
    btn_data1[0] = 0x02;
    btn_data1[1] = 0x0d;
    btn_data1[2] = 0x0a;
    mSerialPort->write(btn_data1);
    if(flag_bee == false)
     {
        ui->btn_bee->setText("关闭");
            flag_bee = true;
     }
    else
     {
        ui->btn_bee->setText("打开");
            flag_bee = false;
     }
}

