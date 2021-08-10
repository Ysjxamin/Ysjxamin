#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "gamewindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("暴躁小杨三国杀");
    //点击"开始游戏"按钮，跳转到游戏窗口
    connect(ui->StartGame,&QPushButton::clicked,
            [=]()
    {
        this->hide();
        game.show();
    });
    //监听游戏窗口的返回信号
    connect(&game,&GameWindow::back,
            [=]()
    {
        game.hide();
        this->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    //背景图
    p.drawPixmap(0,0,width(),height(),QPixmap(":/image/background.png"));
    //按钮图
    QPixmap pixmap;
    pixmap=QPixmap(":/image/button.png");
    pixmap=pixmap.scaled(ui->StartGame->width(),ui->StartGame->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    //开始游戏
    ui->StartGame->setIcon(pixmap);
    ui->StartGame->setIconSize(QSize(ui->StartGame->width(),ui->StartGame->height()));
    QFont ft;
    ft.setPointSize(20);
    ui->label->setFont(ft);
    //武将一览
    ui->GeneView->setIcon(pixmap);
    ui->GeneView->setIconSize(QSize(ui->GeneView->width(),ui->StartGame->height()));
    ui->label2->setFont(ft);
    //卡牌一览
    ui->CardView->setIcon(pixmap);
    ui->CardView->setIconSize(QSize(ui->GeneView->width(),ui->StartGame->height()));
    ui->label3->setFont(ft);
    //关于作者
    ui->AboutMan->setIcon(pixmap);
    ui->AboutMan->setIconSize(QSize(ui->GeneView->width(),ui->StartGame->height()));
    ui->label4->setFont(ft);
    //退出游戏
    ui->ExitGame->setIcon(pixmap);
    ui->ExitGame->setIconSize(QSize(ui->GeneView->width(),ui->StartGame->height()));
    ui->label5->setFont(ft);
    //关于游戏
    ui->AboutGame->setIcon(pixmap);
    ui->AboutGame->setIconSize(QSize(ui->GeneView->width(),ui->StartGame->height()));
    ui->label6->setFont(ft);
}
