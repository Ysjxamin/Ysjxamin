#ifndef HERO_H
#define HERO_H

#include <QWidget>
#include<QDir>
#include<QPaintEvent>
namespace Ui {
class Hero;
}

class Hero : public QWidget
{
    Q_OBJECT

public:
    explicit Hero(QWidget *parent = 0);
      void readhero();
    ~Hero();
signals:
    void back();
private slots:
    void on_pushButton_clicked();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::Hero *ui;
    QDir dir;
    int Imagecount;
    int index;
};

#endif // HERO_H
