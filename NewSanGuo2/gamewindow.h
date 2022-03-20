#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include<QMouseEvent>
#include<QMoveEvent>
#include<QPoint>
#include<QPaintEvent>
#include<QPainter>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
signals:
    void back();

public slots:
protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_Backbutton_clicked();

private:
    Ui::GameWindow *ui;

};

#endif // GAMEWINDOW_H
