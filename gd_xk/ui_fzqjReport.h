/********************************************************************************
** Form generated from reading UI file 'fzqjReport.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FZQJREPORT_H
#define UI_FZQJREPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fzqjReportClass
{
public:
    QWidget *centralWidget;
    QLabel *local_lon_name;
    QLabel *local_lat_name;
    QLabel *local_alt_name;
    QLabel *target_pc_name;
    QLabel *target_dis_name;
    QLabel *target_type;
    QPushButton *btn_report_send;
    QTextEdit *txt_local_lon_value;
    QTextEdit *txt_local_lat_value;
    QTextEdit *txt_local_alt_value;
    QTextEdit *txt_target_Az_value;
    QTextEdit *txt_target_pc_value;
    QTextEdit *txt_target_dis_value;
    QComboBox *cbx_target_type_list;
    QLabel *target_Az_name;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *fzqjReportClass)
    {
        if (fzqjReportClass->objectName().isEmpty())
            fzqjReportClass->setObjectName(QStringLiteral("fzqjReportClass"));
        fzqjReportClass->resize(325, 547);
        fzqjReportClass->setMaximumSize(QSize(325, 547));
        centralWidget = new QWidget(fzqjReportClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        local_lon_name = new QLabel(centralWidget);
        local_lon_name->setObjectName(QStringLiteral("local_lon_name"));
        local_lon_name->setGeometry(QRect(9, 29, 60, 16));
        local_lat_name = new QLabel(centralWidget);
        local_lat_name->setObjectName(QStringLiteral("local_lat_name"));
        local_lat_name->setGeometry(QRect(9, 78, 60, 16));
        local_alt_name = new QLabel(centralWidget);
        local_alt_name->setObjectName(QStringLiteral("local_alt_name"));
        local_alt_name->setGeometry(QRect(9, 127, 60, 16));
        target_pc_name = new QLabel(centralWidget);
        target_pc_name->setObjectName(QStringLiteral("target_pc_name"));
        target_pc_name->setGeometry(QRect(9, 274, 61, 16));
        target_dis_name = new QLabel(centralWidget);
        target_dis_name->setObjectName(QStringLiteral("target_dis_name"));
        target_dis_name->setGeometry(QRect(9, 323, 61, 16));
        target_type = new QLabel(centralWidget);
        target_type->setObjectName(QStringLiteral("target_type"));
        target_type->setGeometry(QRect(9, 176, 61, 16));
        btn_report_send = new QPushButton(centralWidget);
        btn_report_send->setObjectName(QStringLiteral("btn_report_send"));
        btn_report_send->setGeometry(QRect(194, 380, 81, 31));
        txt_local_lon_value = new QTextEdit(centralWidget);
        txt_local_lon_value->setObjectName(QStringLiteral("txt_local_lon_value"));
        txt_local_lon_value->setGeometry(QRect(70, 20, 211, 31));
        txt_local_lat_value = new QTextEdit(centralWidget);
        txt_local_lat_value->setObjectName(QStringLiteral("txt_local_lat_value"));
        txt_local_lat_value->setGeometry(QRect(70, 70, 211, 31));
        txt_local_alt_value = new QTextEdit(centralWidget);
        txt_local_alt_value->setObjectName(QStringLiteral("txt_local_alt_value"));
        txt_local_alt_value->setGeometry(QRect(70, 120, 211, 31));
        txt_target_Az_value = new QTextEdit(centralWidget);
        txt_target_Az_value->setObjectName(QStringLiteral("txt_target_Az_value"));
        txt_target_Az_value->setGeometry(QRect(70, 220, 211, 31));
        txt_target_pc_value = new QTextEdit(centralWidget);
        txt_target_pc_value->setObjectName(QStringLiteral("txt_target_pc_value"));
        txt_target_pc_value->setGeometry(QRect(70, 270, 211, 31));
        txt_target_dis_value = new QTextEdit(centralWidget);
        txt_target_dis_value->setObjectName(QStringLiteral("txt_target_dis_value"));
        txt_target_dis_value->setGeometry(QRect(70, 320, 211, 31));
        cbx_target_type_list = new QComboBox(centralWidget);
        cbx_target_type_list->setObjectName(QStringLiteral("cbx_target_type_list"));
        cbx_target_type_list->setGeometry(QRect(80, 170, 201, 31));
        cbx_target_type_list->setEditable(true);
        target_Az_name = new QLabel(centralWidget);
        target_Az_name->setObjectName(QStringLiteral("target_Az_name"));
        target_Az_name->setGeometry(QRect(9, 225, 61, 16));
        fzqjReportClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(fzqjReportClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 325, 30));
        fzqjReportClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(fzqjReportClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        fzqjReportClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(fzqjReportClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        fzqjReportClass->setStatusBar(statusBar);

        retranslateUi(fzqjReportClass);

        QMetaObject::connectSlotsByName(fzqjReportClass);
    } // setupUi

    void retranslateUi(QMainWindow *fzqjReportClass)
    {
        fzqjReportClass->setWindowTitle(QApplication::translate("fzqjReportClass", "\346\211\213\345\212\250\344\270\212\346\212\245", Q_NULLPTR));
        local_lon_name->setText(QApplication::translate("fzqjReportClass", "\346\234\254\346\234\272\347\273\217\345\272\246\357\274\232", Q_NULLPTR));
        local_lat_name->setText(QApplication::translate("fzqjReportClass", "\346\234\254\346\234\272\347\272\254\345\272\246\357\274\232", Q_NULLPTR));
        local_alt_name->setText(QApplication::translate("fzqjReportClass", "\346\234\254\346\234\272\351\253\230\345\272\246\357\274\232", Q_NULLPTR));
        target_pc_name->setText(QApplication::translate("fzqjReportClass", "\347\233\256\346\240\207\344\277\257\344\273\260\357\274\232", Q_NULLPTR));
        target_dis_name->setText(QApplication::translate("fzqjReportClass", "\347\233\256\346\240\207\350\267\235\347\246\273\357\274\232", Q_NULLPTR));
        target_type->setText(QApplication::translate("fzqjReportClass", "\347\233\256\346\240\207\347\261\273\345\236\213\357\274\232", Q_NULLPTR));
        btn_report_send->setText(QApplication::translate("fzqjReportClass", "\344\270\212\346\212\245", Q_NULLPTR));
        cbx_target_type_list->clear();
        cbx_target_type_list->insertItems(0, QStringList()
         << QApplication::translate("fzqjReportClass", "\344\270\215\346\230\216", Q_NULLPTR)
         << QApplication::translate("fzqjReportClass", "\347\233\264\345\215\207\346\234\272", Q_NULLPTR)
         << QApplication::translate("fzqjReportClass", "\345\233\272\345\256\232\347\277\274\346\227\240\344\272\272\346\234\272", Q_NULLPTR)
         << QApplication::translate("fzqjReportClass", "\346\227\213\347\277\274\346\227\240\344\272\272\346\234\272", Q_NULLPTR)
         << QApplication::translate("fzqjReportClass", "\350\275\246", Q_NULLPTR)
         << QApplication::translate("fzqjReportClass", "\351\270\237", Q_NULLPTR)
         << QApplication::translate("fzqjReportClass", "\347\251\272\351\243\230\347\220\203", Q_NULLPTR)
         << QApplication::translate("fzqjReportClass", "\345\244\247\345\236\213\346\227\240\344\272\272\346\234\272", Q_NULLPTR)
         << QApplication::translate("fzqjReportClass", "\347\251\272\351\243\230\347\211\251", Q_NULLPTR)
        );
        cbx_target_type_list->setCurrentText(QApplication::translate("fzqjReportClass", "\344\270\215\346\230\216", Q_NULLPTR));
        target_Az_name->setText(QApplication::translate("fzqjReportClass", "\347\233\256\346\240\207\346\226\271\344\275\215\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class fzqjReportClass: public Ui_fzqjReportClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FZQJREPORT_H
