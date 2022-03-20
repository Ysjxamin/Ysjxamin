#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewindow.h"
#include"hero.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_AboutMan_clicked();

    void on_GeneView_clicked();

    void on_ExitGame_clicked();

    void on_AboutGame_clicked();

private:
    Ui::MainWindow *ui;
    GameWindow game;
    Hero hero;
};

#endif // MAINWINDOW_H
