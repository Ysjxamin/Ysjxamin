#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPixmap>
#include <QSize>
#include<QMouseEvent>
#include<QMoveEvent>
#include<QPoint>
#include<QLabel>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    //返回按键图案

    QPixmap pixmap;
        pixmap=QPixmap(":/image/backbutton.jpg");
    ui->setupUi(this);
    ui->Backbutton->setIcon(pixmap);
    //ui->Backbutton->resize(50,50);
    ui->Backbutton->setIconSize(QSize(50,50));
    ui->Backbutton->setAttribute(Qt::WA_TranslucentBackground);
    resize(1000,500);
    this->setWindowTitle("暴躁小铭三国杀");

}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_Backbutton_clicked()
{
    emit this->back();
}
void GameWindow::paintEvent(QPaintEvent *event)
{
    //返回键
    ui->Backbutton->resize(50,50);
    //游戏窗口背景图案
    QPixmap pixmap2;
    pixmap2=QPixmap(":/image/background-3.jpg");
    QPainter p(this);
    p.drawPixmap(0,0,this->width(),this->height(),pixmap2);
    //游戏窗口下层图案
    p.drawPixmap(0,(this->height()-(this->height()/6)),(this->width()/8),(this->height()/6),QPixmap(":/i"
                                                                                                    "mage/dashboard-equip.png"));
    //卡片槽
    p.drawPixmap((this->width()/8),(this->height()-(this->height()/6)),(this->width()*6/8),(this->height()/6),QPixmap(":/image/card-container.png"));
    //游戏玩家
    p.drawPixmap((this->width()*7/8),(this->height()-(this->height()/6)),(this->width()*1/8),(this->height()/6),QPixmap(":/image/dashboard-avatar.png"));
    //设置按钮位置
    ui->pushButton_3->move((this->width()*7/8)+10,(this->height()-(this->height()/6)-35));
    ui->pushButton_2->move((this->width()*7/8)-30,(this->height()-(this->height()/6)-35));
    ui->pushButton->move((this->width()*7/8)-70,(this->height()-(this->height()/6)-35));
    ui->pushButton->setText("确定");
    ui->pushButton_2->setText("取消");
    ui->pushButton_3->setText("结束");
    //游戏玩家二界面
    p.drawPixmap((this->width()*7/8),0,(this->width()*1/8),(this->height()/6),QPixmap(":/image/dashboard-avatar.png"));
    p.drawPixmap((this->width()/8),0,(this->width()*6/8),(this->height()/6),QPixmap(":/image/card-container.png"));
    //设置按钮位置
    ui->pushButton_6->move((this->width()*7/8)+10,(this->height()/6));
    ui->pushButton_5->move((this->width()*7/8)-30,(this->height()/6));
    ui->pushButton_4->move((this->width()*7/8)-70,(this->height()/6));
    ui->pushButton_4->setText("确定");
    ui->pushButton_5->setText("取消");
    ui->pushButton_6->setText("结束");
    //设置血量位置
    ui->hp->resize(10,10);
}
