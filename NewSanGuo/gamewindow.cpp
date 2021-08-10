#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    QPushButton* backbutton=new QPushButton(this);
    backbutton->move(0,0);
    backbutton->setFixedSize(200,100);
    connect(backbutton,&QPushButton::clicked,
            [=]()
    {
        emit this->back();
    });
    resize(1000,500);
    this->setWindowTitle("暴躁小铭三国杀");
}

GameWindow::~GameWindow()
{
    delete ui;
}
