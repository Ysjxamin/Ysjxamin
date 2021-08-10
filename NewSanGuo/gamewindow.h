#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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
private:
    QPushButton backbutton;
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
