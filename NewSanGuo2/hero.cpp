#include "hero.h"
#include "ui_hero.h"
#include<QList>
#include<QDir>
#include<QLabel>
#include<QPixmap>
#include<QDebug>
#include<QString>
#include<QFileDialog>
#include<QLineEdit>

Hero::Hero(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hero)
{
    ui->setupUi(this);
}

Hero::~Hero()
{
    delete ui;
}

void Hero::on_pushButton_clicked()
{
    index=ui->comboBox->currentIndex();
    qDebug()<<index+1;
    QString str0=QString::number(index+1,10);
    ui->textEdit_2->insertPlainText(str0);

    //index=ui->comboBox->currentIndex();
    //ui->lineEdit->insert('index');
   /* connect(ui->comboBox,&QComboBox::currentIndexChanged(index),
            [=]()
    {
        Hero::on_comboBox_currentIndexChanged(index);
    });*/
}
void Hero::paintEvent(QPaintEvent *event)
{
    QPixmap pixmap;
    QIcon   icon;
       // ui->comboBox->clear(); //清除列表
        for (int i=1;i<20;i++)
        {
            QString imagename=":/image/Screen Shot 2017-01-13 at 11.17.56.png";
            pixmap=QPixmap(imagename);
            icon=(QIcon(pixmap));
            ui->comboBox->addItem(icon,QString::asprintf("英雄 %d",i)); //带图标
           // ui->comboBox->addItem(QString::asprintf("Item %d",i)); //不带图标
        }

}
void Hero::readhero()
{
    int i=1;
    //指定路径
    QString path=QFileDialog::getOpenFileName(this,"AMIN","./","TXT(*.txt)");

    if(!path.isEmpty())
    {
    //文件对象创建
    QFile file(path);
    //打开文件，只读方式
    if(file.open(QIODevice::ReadOnly))
    {
#if 0
    //读文件 默认只识别UTF8编码
    QByteArray array=file.readAll();
    //显示到编辑区
    ui->textEdit->setText(array);
#endif
    //读文件 默认只识别UTF8编码
    QByteArray array;
    QString str[200];
    QTextCursor cursor=ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
    while(!file.atEnd())
    {
       //读一行
        //array+=file.readLine();
        str[i]=QString(file.readLine().data());
        ui->textEdit->insertPlainText(str[i]);
        i++;
    }
   // ui->textEdit->insertPlainText(QString('\n'));
   // ui->textEdit->setText(str[2]);
    }
      file.close();
    }
}
