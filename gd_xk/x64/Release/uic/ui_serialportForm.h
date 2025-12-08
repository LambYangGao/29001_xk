/********************************************************************************
** Form generated from reading UI file 'serialportForm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALPORTFORM_H
#define UI_SERIALPORTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serialportForm
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QComboBox *cbx_portname;
    QLabel *label_2;
    QComboBox *cbx_baudrate;
    QComboBox *cbx_databits;
    QComboBox *cbx_stopbits;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *cbx_parity;
    QComboBox *cbx_flowcontrol;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *btn_open;

    void setupUi(QWidget *serialportForm)
    {
        if (serialportForm->objectName().isEmpty())
            serialportForm->setObjectName(QStringLiteral("serialportForm"));
        serialportForm->resize(246, 298);
        serialportForm->setMaximumSize(QSize(246, 298));
        groupBox = new QGroupBox(serialportForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 201, 211));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 41, 16));
        cbx_portname = new QComboBox(groupBox);
        cbx_portname->setObjectName(QStringLiteral("cbx_portname"));
        cbx_portname->setGeometry(QRect(70, 30, 101, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 60, 41, 16));
        cbx_baudrate = new QComboBox(groupBox);
        cbx_baudrate->setObjectName(QStringLiteral("cbx_baudrate"));
        cbx_baudrate->setGeometry(QRect(70, 60, 101, 16));
        cbx_databits = new QComboBox(groupBox);
        cbx_databits->setObjectName(QStringLiteral("cbx_databits"));
        cbx_databits->setGeometry(QRect(70, 90, 101, 16));
        cbx_stopbits = new QComboBox(groupBox);
        cbx_stopbits->setObjectName(QStringLiteral("cbx_stopbits"));
        cbx_stopbits->setGeometry(QRect(70, 120, 101, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 90, 41, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 120, 41, 16));
        cbx_parity = new QComboBox(groupBox);
        cbx_parity->setObjectName(QStringLiteral("cbx_parity"));
        cbx_parity->setGeometry(QRect(70, 150, 101, 16));
        cbx_flowcontrol = new QComboBox(groupBox);
        cbx_flowcontrol->setObjectName(QStringLiteral("cbx_flowcontrol"));
        cbx_flowcontrol->setGeometry(QRect(70, 180, 101, 16));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 150, 41, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 180, 61, 16));
        btn_open = new QPushButton(serialportForm);
        btn_open->setObjectName(QStringLiteral("btn_open"));
        btn_open->setGeometry(QRect(140, 240, 81, 21));

        retranslateUi(serialportForm);

        cbx_baudrate->setCurrentIndex(4);
        cbx_databits->setCurrentIndex(3);
        cbx_parity->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(serialportForm);
    } // setupUi

    void retranslateUi(QWidget *serialportForm)
    {
        serialportForm->setWindowTitle(QApplication::translate("serialportForm", "\344\270\262\345\217\243\345\217\202\346\225\260\350\256\276\347\275\256", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("serialportForm", "settings", Q_NULLPTR));
        label->setText(QApplication::translate("serialportForm", "portname", Q_NULLPTR));
        label_2->setText(QApplication::translate("serialportForm", "baud rate", Q_NULLPTR));
        cbx_baudrate->clear();
        cbx_baudrate->insertItems(0, QStringList()
         << QApplication::translate("serialportForm", "1200", Q_NULLPTR)
         << QApplication::translate("serialportForm", "2400", Q_NULLPTR)
         << QApplication::translate("serialportForm", "4800", Q_NULLPTR)
         << QApplication::translate("serialportForm", "9600", Q_NULLPTR)
         << QApplication::translate("serialportForm", "19200", Q_NULLPTR)
         << QApplication::translate("serialportForm", "38400", Q_NULLPTR)
         << QApplication::translate("serialportForm", "57600", Q_NULLPTR)
         << QApplication::translate("serialportForm", "115200", Q_NULLPTR)
        );
        cbx_baudrate->setCurrentText(QApplication::translate("serialportForm", "19200", Q_NULLPTR));
        cbx_databits->clear();
        cbx_databits->insertItems(0, QStringList()
         << QApplication::translate("serialportForm", "5", Q_NULLPTR)
         << QApplication::translate("serialportForm", "6", Q_NULLPTR)
         << QApplication::translate("serialportForm", "7", Q_NULLPTR)
         << QApplication::translate("serialportForm", "8", Q_NULLPTR)
        );
        cbx_stopbits->clear();
        cbx_stopbits->insertItems(0, QStringList()
         << QApplication::translate("serialportForm", "1", Q_NULLPTR)
         << QApplication::translate("serialportForm", "2", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("serialportForm", "data bits", Q_NULLPTR));
        label_4->setText(QApplication::translate("serialportForm", "stop bits", Q_NULLPTR));
        cbx_parity->clear();
        cbx_parity->insertItems(0, QStringList()
         << QApplication::translate("serialportForm", "O", Q_NULLPTR)
         << QApplication::translate("serialportForm", "E", Q_NULLPTR)
         << QApplication::translate("serialportForm", "N", Q_NULLPTR)
        );
        cbx_flowcontrol->clear();
        cbx_flowcontrol->insertItems(0, QStringList()
         << QApplication::translate("serialportForm", "NoFlowControl", Q_NULLPTR)
        );
        label_5->setText(QApplication::translate("serialportForm", "parity", Q_NULLPTR));
        label_6->setText(QApplication::translate("serialportForm", "flow control", Q_NULLPTR));
        btn_open->setText(QApplication::translate("serialportForm", "\350\256\276\347\275\256\345\217\202\346\225\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class serialportForm: public Ui_serialportForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALPORTFORM_H
