/********************************************************************************
** Form generated from reading UI file 'database.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASE_H
#define UI_DATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataBase
{
public:
    QTableView *tableView;
    QPushButton *pushButton;
    QPushButton *lookfor;
    QPushButton *clearquery;
    QPushButton *setorder;
    QPushButton *showall;
    QPushButton *pushButton_6;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_7;

    void setupUi(QWidget *DataBase)
    {
        if (DataBase->objectName().isEmpty())
            DataBase->setObjectName(QStringLiteral("DataBase"));
        DataBase->resize(623, 483);
        tableView = new QTableView(DataBase);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(20, 10, 281, 461));
        pushButton = new QPushButton(DataBase);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(350, 70, 75, 23));
        lookfor = new QPushButton(DataBase);
        lookfor->setObjectName(QStringLiteral("lookfor"));
        lookfor->setGeometry(QRect(350, 120, 75, 23));
        clearquery = new QPushButton(DataBase);
        clearquery->setObjectName(QStringLiteral("clearquery"));
        clearquery->setGeometry(QRect(480, 70, 75, 23));
        setorder = new QPushButton(DataBase);
        setorder->setObjectName(QStringLiteral("setorder"));
        setorder->setGeometry(QRect(480, 120, 75, 23));
        showall = new QPushButton(DataBase);
        showall->setObjectName(QStringLiteral("showall"));
        showall->setGeometry(QRect(350, 170, 75, 23));
        pushButton_6 = new QPushButton(DataBase);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(470, 170, 75, 23));
        label = new QLabel(DataBase);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(340, 240, 54, 12));
        lineEdit = new QLineEdit(DataBase);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(410, 240, 113, 20));
        pushButton_7 = new QPushButton(DataBase);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(540, 240, 75, 23));

        retranslateUi(DataBase);

        QMetaObject::connectSlotsByName(DataBase);
    } // setupUi

    void retranslateUi(QWidget *DataBase)
    {
        DataBase->setWindowTitle(QApplication::translate("DataBase", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DataBase", "\346\267\273\345\212\240", Q_NULLPTR));
        lookfor->setText(QApplication::translate("DataBase", "\346\237\245\350\257\242", Q_NULLPTR));
        clearquery->setText(QApplication::translate("DataBase", "\346\270\205\347\251\272", Q_NULLPTR));
        setorder->setText(QApplication::translate("DataBase", "\346\216\222\345\272\217", Q_NULLPTR));
        showall->setText(QApplication::translate("DataBase", "\346\230\276\347\244\272\345\205\250\350\241\250", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("DataBase", "PushButton", Q_NULLPTR));
        label->setText(QApplication::translate("DataBase", "TextLabel", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("DataBase", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DataBase: public Ui_DataBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASE_H
