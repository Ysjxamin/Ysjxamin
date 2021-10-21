/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *btn_send;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *Cboxport;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *Cboxboudrate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *Cboxparity;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *Cboxdatabits;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *Cboxstopbits;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btn_open;
    QSpacerItem *verticalSpacer;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEdit_Recv;
    QSpacerItem *verticalSpacer_2;
    QTextEdit *textEdit_send;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *btn_yellow;
    QPushButton *btn_red;
    QLabel *label_9;
    QLabel *label_10;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_11;
    QPushButton *btn_bee;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_12;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_13;
    QLineEdit *line_Temp;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_14;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_15;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_16;
    QLineEdit *lineEdit_5;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(1148, 754);
        btn_send = new QPushButton(Dialog);
        btn_send->setObjectName(QStringLiteral("btn_send"));
        btn_send->setGeometry(QRect(620, 290, 93, 28));
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(140, 40, 151, 381));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        Cboxport = new QComboBox(layoutWidget);
        Cboxport->setObjectName(QStringLiteral("Cboxport"));

        horizontalLayout->addWidget(Cboxport);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        Cboxboudrate = new QComboBox(layoutWidget);
        Cboxboudrate->setObjectName(QStringLiteral("Cboxboudrate"));

        horizontalLayout_2->addWidget(Cboxboudrate);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        Cboxparity = new QComboBox(layoutWidget);
        Cboxparity->setObjectName(QStringLiteral("Cboxparity"));

        horizontalLayout_3->addWidget(Cboxparity);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        Cboxdatabits = new QComboBox(layoutWidget);
        Cboxdatabits->setObjectName(QStringLiteral("Cboxdatabits"));

        horizontalLayout_4->addWidget(Cboxdatabits);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        Cboxstopbits = new QComboBox(layoutWidget);
        Cboxstopbits->setObjectName(QStringLiteral("Cboxstopbits"));

        horizontalLayout_5->addWidget(Cboxstopbits);


        verticalLayout->addLayout(horizontalLayout_5);

        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(170, 450, 95, 112));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        btn_open = new QPushButton(layoutWidget1);
        btn_open->setObjectName(QStringLiteral("btn_open"));

        verticalLayout_2->addWidget(btn_open);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        layoutWidget2 = new QWidget(Dialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(390, 40, 321, 241));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        textEdit_Recv = new QTextEdit(layoutWidget2);
        textEdit_Recv->setObjectName(QStringLiteral("textEdit_Recv"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(textEdit_Recv->sizePolicy().hasHeightForWidth());
        textEdit_Recv->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(textEdit_Recv);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        textEdit_send = new QTextEdit(layoutWidget2);
        textEdit_send->setObjectName(QStringLiteral("textEdit_send"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(textEdit_send->sizePolicy().hasHeightForWidth());
        textEdit_send->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(textEdit_send);

        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(330, 50, 51, 16));
        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(330, 200, 51, 16));
        label_8 = new QLabel(Dialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(380, 370, 91, 16));
        btn_yellow = new QPushButton(Dialog);
        btn_yellow->setObjectName(QStringLiteral("btn_yellow"));
        btn_yellow->setGeometry(QRect(420, 450, 93, 28));
        btn_red = new QPushButton(Dialog);
        btn_red->setObjectName(QStringLiteral("btn_red"));
        btn_red->setGeometry(QRect(600, 450, 93, 28));
        label_9 = new QLabel(Dialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(430, 420, 68, 15));
        label_10 = new QLabel(Dialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(610, 420, 68, 15));
        layoutWidget3 = new QWidget(Dialog);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(440, 520, 147, 30));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget3);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_6->addWidget(label_11);

        btn_bee = new QPushButton(layoutWidget3);
        btn_bee->setObjectName(QStringLiteral("btn_bee"));

        horizontalLayout_6->addWidget(btn_bee);

        layoutWidget_2 = new QWidget(Dialog);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(730, 20, 361, 281));
        verticalLayout_4 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_12 = new QLabel(layoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_7->addWidget(label_12);

        lineEdit = new QLineEdit(layoutWidget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_7->addWidget(lineEdit);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_13 = new QLabel(layoutWidget_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_8->addWidget(label_13);

        line_Temp = new QLineEdit(layoutWidget_2);
        line_Temp->setObjectName(QStringLiteral("line_Temp"));

        horizontalLayout_8->addWidget(line_Temp);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_14 = new QLabel(layoutWidget_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_9->addWidget(label_14);

        lineEdit_3 = new QLineEdit(layoutWidget_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_9->addWidget(lineEdit_3);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_15 = new QLabel(layoutWidget_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_10->addWidget(label_15);

        lineEdit_4 = new QLineEdit(layoutWidget_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        horizontalLayout_10->addWidget(lineEdit_4);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_16 = new QLabel(layoutWidget_2);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_11->addWidget(label_16);

        lineEdit_5 = new QLineEdit(layoutWidget_2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        horizontalLayout_11->addWidget(lineEdit_5);


        verticalLayout_4->addLayout(horizontalLayout_11);

        QWidget::setTabOrder(btn_yellow, Cboxport);
        QWidget::setTabOrder(Cboxport, Cboxboudrate);
        QWidget::setTabOrder(Cboxboudrate, Cboxparity);
        QWidget::setTabOrder(Cboxparity, Cboxdatabits);
        QWidget::setTabOrder(Cboxdatabits, Cboxstopbits);
        QWidget::setTabOrder(Cboxstopbits, btn_open);
        QWidget::setTabOrder(btn_open, textEdit_Recv);
        QWidget::setTabOrder(textEdit_Recv, btn_red);
        QWidget::setTabOrder(btn_red, btn_bee);
        QWidget::setTabOrder(btn_bee, btn_send);
        QWidget::setTabOrder(btn_send, textEdit_send);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "\345\244\232\345\256\277\350\210\215\347\256\241\347\220\206\347\263\273\347\273\237", Q_NULLPTR));
        btn_send->setText(QApplication::translate("Dialog", "\345\217\221\351\200\201", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog", "\344\270\262\345\217\243\345\217\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog", "\346\263\242\347\211\271\347\216\207", Q_NULLPTR));
        Cboxboudrate->clear();
        Cboxboudrate->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "9600", Q_NULLPTR)
         << QApplication::translate("Dialog", "115200", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("Dialog", "\346\240\241\351\252\214\344\275\215", Q_NULLPTR));
        Cboxparity->clear();
        Cboxparity->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "NONE", Q_NULLPTR)
         << QApplication::translate("Dialog", "ODD", Q_NULLPTR)
         << QApplication::translate("Dialog", "EVEN", Q_NULLPTR)
         << QApplication::translate("Dialog", "MARK", Q_NULLPTR)
         << QApplication::translate("Dialog", "SPACE", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("Dialog", "\346\225\260\346\215\256\344\275\215", Q_NULLPTR));
        Cboxdatabits->clear();
        Cboxdatabits->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "5", Q_NULLPTR)
         << QApplication::translate("Dialog", "6", Q_NULLPTR)
         << QApplication::translate("Dialog", "7", Q_NULLPTR)
         << QApplication::translate("Dialog", "8", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("Dialog", "\345\201\234\346\255\242\344\275\215", Q_NULLPTR));
        Cboxstopbits->clear();
        Cboxstopbits->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "1", Q_NULLPTR)
         << QApplication::translate("Dialog", "1.5", Q_NULLPTR)
         << QApplication::translate("Dialog", "2", Q_NULLPTR)
        );
        btn_open->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200", Q_NULLPTR));
        label_6->setText(QApplication::translate("Dialog", "\346\216\245\346\224\266\345\214\272\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("Dialog", "\345\217\221\351\200\201\345\214\272\357\274\232", Q_NULLPTR));
        label_8->setText(QApplication::translate("Dialog", "\344\270\213\344\275\215\346\234\272\346\216\247\345\210\266\357\274\232", Q_NULLPTR));
        btn_yellow->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200", Q_NULLPTR));
        btn_red->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200", Q_NULLPTR));
        label_9->setText(QApplication::translate("Dialog", "\351\273\204\350\211\262LED", Q_NULLPTR));
        label_10->setText(QApplication::translate("Dialog", "\347\272\242\350\211\262LED", Q_NULLPTR));
        label_11->setText(QApplication::translate("Dialog", "\350\234\202\351\270\243\345\231\250", Q_NULLPTR));
        btn_bee->setText(QApplication::translate("Dialog", "\346\211\223\345\274\200", Q_NULLPTR));
        label_12->setText(QApplication::translate("Dialog", "\346\225\231\345\256\244\347\274\226\345\217\267", Q_NULLPTR));
        label_13->setText(QApplication::translate("Dialog", "\345\256\244\345\206\205\346\270\251\345\272\246", Q_NULLPTR));
        label_14->setText(QApplication::translate("Dialog", "\345\256\244\345\206\205\346\271\277\345\272\246", Q_NULLPTR));
        label_15->setText(QApplication::translate("Dialog", "\345\267\245\344\275\234\346\250\241\345\274\217", Q_NULLPTR));
        label_16->setText(QApplication::translate("Dialog", "\345\256\244\345\206\205\344\272\272\346\225\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
