/********************************************************************************
** Form generated from reading UI file 'serialgetdata.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALGETDATA_H
#define UI_SERIALGETDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SerialGetData
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QComboBox *serialPortBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *baudRateBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QComboBox *stopBitBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *chekBitBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QComboBox *dataBitBox;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *scanSerialBtn;
    QPushButton *openSerialBtn;
    QGroupBox *groupBox_2;
    QDateTimeEdit *dateTimeEdit;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLabel *labelBhao;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QLCDNumber *lcdHuim;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QLabel *labelXming;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *eConnectBtn;
    QPushButton *eDisconnectBtn;
    QPushButton *eDisconnectBtn_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SerialGetData)
    {
        if (SerialGetData->objectName().isEmpty())
            SerialGetData->setObjectName(QStringLiteral("SerialGetData"));
        SerialGetData->resize(800, 600);
        QFont font;
        font.setPointSize(9);
        SerialGetData->setFont(font);
        SerialGetData->setCursor(QCursor(Qt::OpenHandCursor));
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/icon/temp.png"), QSize(), QIcon::Normal, QIcon::Off);
        SerialGetData->setWindowIcon(icon);
        SerialGetData->setStyleSheet(QLatin1String("\n"
"background-color: rgb(0, 0, 0);"));
        SerialGetData->setIconSize(QSize(24, 24));
        centralwidget = new QWidget(SerialGetData);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 221, 351));
        QFont font1;
        font1.setPointSize(13);
        groupBox->setFont(font1);
        groupBox->setStyleSheet(QStringLiteral("color: rgb(0, 255, 255);"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_5->addWidget(label);

        serialPortBox = new QComboBox(groupBox);
        serialPortBox->setObjectName(QStringLiteral("serialPortBox"));
        QFont font2;
        font2.setFamily(QStringLiteral("Agency FB"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        serialPortBox->setFont(font2);
        serialPortBox->setStyleSheet(QLatin1String("color: rgb(255, 0, 127);\n"
"background-color: rgb(170, 255, 255);\n"
""));

        horizontalLayout_5->addWidget(serialPortBox);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 9);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        baudRateBox = new QComboBox(groupBox);
        baudRateBox->setObjectName(QStringLiteral("baudRateBox"));
        baudRateBox->setFont(font2);
        baudRateBox->setStyleSheet(QLatin1String("color: rgb(255, 0, 127);\n"
"background-color: rgb(170, 255, 255);"));

        horizontalLayout->addWidget(baudRateBox);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 9);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        stopBitBox = new QComboBox(groupBox);
        stopBitBox->setObjectName(QStringLiteral("stopBitBox"));
        stopBitBox->setFont(font2);
        stopBitBox->setStyleSheet(QLatin1String("color: rgb(255, 0, 127);\n"
"background-color: rgb(170, 255, 255);"));

        horizontalLayout_4->addWidget(stopBitBox);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 9);

        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        chekBitBox = new QComboBox(groupBox);
        chekBitBox->setObjectName(QStringLiteral("chekBitBox"));
        chekBitBox->setFont(font2);
        chekBitBox->setStyleSheet(QLatin1String("color: rgb(255, 0, 127);\n"
"background-color: rgb(170, 255, 255);"));

        horizontalLayout_3->addWidget(chekBitBox);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 9);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        dataBitBox = new QComboBox(groupBox);
        dataBitBox->setObjectName(QStringLiteral("dataBitBox"));
        dataBitBox->setFont(font2);
        dataBitBox->setStyleSheet(QLatin1String("color: rgb(255, 0, 127);\n"
"background-color: rgb(170, 255, 255);"));

        horizontalLayout_2->addWidget(dataBitBox);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 9);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        scanSerialBtn = new QPushButton(groupBox);
        scanSerialBtn->setObjectName(QStringLiteral("scanSerialBtn"));
        QFont font3;
        font3.setPointSize(9);
        font3.setBold(true);
        font3.setWeight(75);
        scanSerialBtn->setFont(font3);
        scanSerialBtn->setStyleSheet(QLatin1String("background-color: rgb(0, 255, 255);\n"
"color: rgb(0, 0, 255);\n"
"border-color: rgb(255, 0, 0);"));

        horizontalLayout_6->addWidget(scanSerialBtn);

        openSerialBtn = new QPushButton(groupBox);
        openSerialBtn->setObjectName(QStringLiteral("openSerialBtn"));
        openSerialBtn->setFont(font3);
        openSerialBtn->setStyleSheet(QLatin1String("background-color: rgb(0, 255, 255);\n"
"color: rgb(0, 0, 255);\n"
"border-color: rgb(255, 0, 0);"));

        horizontalLayout_6->addWidget(openSerialBtn);


        verticalLayout->addLayout(horizontalLayout_6);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 390, 721, 161));
        QFont font4;
        font4.setPointSize(12);
        groupBox_2->setFont(font4);
        groupBox_2->setStyleSheet(QStringLiteral("color: rgb(255, 255, 0);"));
        dateTimeEdit = new QDateTimeEdit(groupBox_2);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(20, 40, 681, 101));
        QFont font5;
        font5.setPointSize(37);
        dateTimeEdit->setFont(font5);
        dateTimeEdit->setCursor(QCursor(Qt::PointingHandCursor));
        dateTimeEdit->setStyleSheet(QLatin1String("color: rgb(255, 0, 255);\n"
"gridline-color: rgb(255, 0, 0);\n"
"background-color: rgb(0, 0, 0);\n"
"boder:none;"));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(250, 10, 471, 391));
        QFont font6;
        font6.setPointSize(16);
        groupBox_3->setFont(font6);
        groupBox_3->setStyleSheet(QStringLiteral("color: rgb(0, 0, 255);"));
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 30, 400, 321));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font7;
        font7.setPointSize(18);
        font7.setBold(true);
        font7.setWeight(75);
        label_6->setFont(font7);
        label_6->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));

        horizontalLayout_7->addWidget(label_6);

        labelBhao = new QLabel(layoutWidget);
        labelBhao->setObjectName(QStringLiteral("labelBhao"));
        labelBhao->setFont(font7);
        labelBhao->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));

        horizontalLayout_7->addWidget(labelBhao);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font7);
        label_7->setStyleSheet(QStringLiteral("color: rgb(0, 255, 255);"));

        horizontalLayout_8->addWidget(label_7);

        lcdHuim = new QLCDNumber(layoutWidget);
        lcdHuim->setObjectName(QStringLiteral("lcdHuim"));
        lcdHuim->setStyleSheet(QLatin1String("color: rgb(170, 255, 255);\n"
"border-color: rgb(0, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));

        horizontalLayout_8->addWidget(lcdHuim);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font7);
        label_10->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));

        horizontalLayout_10->addWidget(label_10);

        labelXming = new QLabel(layoutWidget);
        labelXming->setObjectName(QStringLiteral("labelXming"));
        labelXming->setFont(font7);
        labelXming->setStyleSheet(QStringLiteral("color: rgb(255, 0, 0);"));

        horizontalLayout_10->addWidget(labelXming);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        eConnectBtn = new QPushButton(layoutWidget);
        eConnectBtn->setObjectName(QStringLiteral("eConnectBtn"));
        QFont font8;
        font8.setFamily(QStringLiteral("Agency FB"));
        font8.setPointSize(16);
        font8.setBold(true);
        font8.setItalic(false);
        font8.setWeight(75);
        eConnectBtn->setFont(font8);
        eConnectBtn->setStyleSheet(QLatin1String("background-color: rgb(0, 255, 255);\n"
"border-color: rgb(255, 0, 0);"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/image/icon/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
        eConnectBtn->setIcon(icon1);
        eConnectBtn->setIconSize(QSize(30, 30));

        horizontalLayout_13->addWidget(eConnectBtn);

        eDisconnectBtn = new QPushButton(layoutWidget);
        eDisconnectBtn->setObjectName(QStringLiteral("eDisconnectBtn"));
        QFont font9;
        font9.setFamily(QStringLiteral("Agency FB"));
        font9.setPointSize(16);
        font9.setBold(true);
        font9.setWeight(75);
        eDisconnectBtn->setFont(font9);
        eDisconnectBtn->setStyleSheet(QLatin1String("background-color: rgb(0, 255, 255);\n"
"border-color: rgb(255, 0, 0);"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/image/icon/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        eDisconnectBtn->setIcon(icon2);
        eDisconnectBtn->setIconSize(QSize(30, 30));

        horizontalLayout_13->addWidget(eDisconnectBtn);

        eDisconnectBtn_2 = new QPushButton(layoutWidget);
        eDisconnectBtn_2->setObjectName(QStringLiteral("eDisconnectBtn_2"));
        eDisconnectBtn_2->setFont(font9);
        eDisconnectBtn_2->setStyleSheet(QLatin1String("background-color: rgb(0, 255, 255);\n"
"border-color: rgb(255, 0, 0);"));
        eDisconnectBtn_2->setIcon(icon2);
        eDisconnectBtn_2->setIconSize(QSize(30, 30));

        horizontalLayout_13->addWidget(eDisconnectBtn_2);


        verticalLayout_2->addLayout(horizontalLayout_13);

        SerialGetData->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SerialGetData);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        SerialGetData->setMenuBar(menubar);
        statusbar = new QStatusBar(SerialGetData);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        SerialGetData->setStatusBar(statusbar);

        retranslateUi(SerialGetData);

        QMetaObject::connectSlotsByName(SerialGetData);
    } // setupUi

    void retranslateUi(QMainWindow *SerialGetData)
    {
        SerialGetData->setWindowTitle(QApplication::translate("SerialGetData", "\346\270\251\346\271\277\345\272\246\346\230\276\347\244\272\347\273\210\347\253\257", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SerialGetData", "\344\270\262\345\217\243\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("SerialGetData", "\344\270\262\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        serialPortBox->clear();
        serialPortBox->insertItems(0, QStringList()
         << QApplication::translate("SerialGetData", "COM1", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "COM2", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "COM3", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("SerialGetData", "\346\263\242\347\211\271\347\216\207\357\274\232", Q_NULLPTR));
        baudRateBox->clear();
        baudRateBox->insertItems(0, QStringList()
         << QApplication::translate("SerialGetData", "115200", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "1200", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "2400", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "4800", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "9600", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "14400", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "19200", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "38400", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "56000", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "57600", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("SerialGetData", "\345\201\234\346\255\242\344\275\215\357\274\232", Q_NULLPTR));
        stopBitBox->clear();
        stopBitBox->insertItems(0, QStringList()
         << QApplication::translate("SerialGetData", "1", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "2", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("SerialGetData", "\346\240\241\351\252\214\344\275\215\357\274\232", Q_NULLPTR));
        chekBitBox->clear();
        chekBitBox->insertItems(0, QStringList()
         << QApplication::translate("SerialGetData", "None", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("SerialGetData", "\346\225\260\346\215\256\344\275\215\357\274\232", Q_NULLPTR));
        dataBitBox->clear();
        dataBitBox->insertItems(0, QStringList()
         << QApplication::translate("SerialGetData", "8", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "7", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "6", Q_NULLPTR)
         << QApplication::translate("SerialGetData", "5", Q_NULLPTR)
        );
        scanSerialBtn->setText(QApplication::translate("SerialGetData", "\346\211\253\346\217\217\344\270\262\345\217\243", Q_NULLPTR));
        openSerialBtn->setText(QApplication::translate("SerialGetData", "\346\211\223\345\274\200\344\270\262\345\217\243", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("SerialGetData", "\345\256\236\346\227\266\346\227\266\351\222\237\357\274\232", Q_NULLPTR));
        dateTimeEdit->setDisplayFormat(QApplication::translate("SerialGetData", "yyyy/MM/dd H:mm:ss", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("SerialGetData", "\346\243\200\346\265\213\344\272\272\344\277\241\346\201\257\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("SerialGetData", "ID:", Q_NULLPTR));
        labelBhao->setText(QString());
        label_7->setText(QApplication::translate("SerialGetData", "\347\274\226\345\217\267\357\274\232", Q_NULLPTR));
        label_10->setText(QApplication::translate("SerialGetData", "\345\247\223\345\220\215\357\274\232", Q_NULLPTR));
        labelXming->setText(QString());
        eConnectBtn->setText(QApplication::translate("SerialGetData", "\345\273\272\347\253\213\350\277\236\346\216\245", Q_NULLPTR));
        eDisconnectBtn->setText(QApplication::translate("SerialGetData", "\345\205\263\351\227\255\350\277\236\346\216\245", Q_NULLPTR));
        eDisconnectBtn_2->setText(QApplication::translate("SerialGetData", "\346\237\245\347\234\213\346\225\260\346\215\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SerialGetData: public Ui_SerialGetData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALGETDATA_H
