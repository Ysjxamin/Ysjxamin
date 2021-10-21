#ifndef SYSTEM_H
#define SYSTEM_H

#include <QWidget>

namespace Ui {
class System;
}

class System : public QWidget
{
    Q_OBJECT

public:
    explicit System(QWidget *parent = 0);
    ~System();

private:
    Ui::System *ui;
private slots:

};

#endif // SYSTEM_H
