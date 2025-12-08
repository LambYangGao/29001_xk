/********************************************************************************
** Form generated from reading UI file 'fzqjViMore.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FZQJVIMORE_H
#define UI_FZQJVIMORE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fzqjViMoreClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *btn_vi_focuse_auto;
    QPushButton *btn_vi_focuse_manul;
    QPushButton *btn_vi_focuse_semiAuto;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_72;
    QLabel *label_52;
    QSpinBox *spinbox_qw_level_2;
    QToolButton *btn_vl_qw_open_2;
    QHBoxLayout *horizontalLayout_227;
    QLabel *label_235;
    QToolButton *btn_vl_display_mode_heibai;
    QToolButton *btn_vl_display_mode_caise;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_229;
    QLabel *label_237;
    QToolButton *btn_vl_black_target;
    QToolButton *btn_vl_write_target;
    QHBoxLayout *horizontalLayout_230;
    QLabel *label_238;
    QToolButton *btn_vl_auto_track;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *txt_vi_send;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_vi_send;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *fzqjViMoreClass)
    {
        if (fzqjViMoreClass->objectName().isEmpty())
            fzqjViMoreClass->setObjectName(QStringLiteral("fzqjViMoreClass"));
        fzqjViMoreClass->resize(467, 365);
        fzqjViMoreClass->setMaximumSize(QSize(472, 374));
        centralWidget = new QWidget(fzqjViMoreClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        btn_vi_focuse_auto = new QPushButton(centralWidget);
        btn_vi_focuse_auto->setObjectName(QStringLiteral("btn_vi_focuse_auto"));
        btn_vi_focuse_auto->setFont(font);

        horizontalLayout->addWidget(btn_vi_focuse_auto);

        btn_vi_focuse_manul = new QPushButton(centralWidget);
        btn_vi_focuse_manul->setObjectName(QStringLiteral("btn_vi_focuse_manul"));
        btn_vi_focuse_manul->setFont(font);

        horizontalLayout->addWidget(btn_vi_focuse_manul);

        btn_vi_focuse_semiAuto = new QPushButton(centralWidget);
        btn_vi_focuse_semiAuto->setObjectName(QStringLiteral("btn_vi_focuse_semiAuto"));
        btn_vi_focuse_semiAuto->setFont(font);

        horizontalLayout->addWidget(btn_vi_focuse_semiAuto);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_72 = new QHBoxLayout();
        horizontalLayout_72->setSpacing(6);
        horizontalLayout_72->setObjectName(QStringLiteral("horizontalLayout_72"));
        label_52 = new QLabel(centralWidget);
        label_52->setObjectName(QStringLiteral("label_52"));
        label_52->setMaximumSize(QSize(80, 16777215));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        label_52->setFont(font1);

        horizontalLayout_72->addWidget(label_52);

        spinbox_qw_level_2 = new QSpinBox(centralWidget);
        spinbox_qw_level_2->setObjectName(QStringLiteral("spinbox_qw_level_2"));
        spinbox_qw_level_2->setMaximum(10);

        horizontalLayout_72->addWidget(spinbox_qw_level_2);

        btn_vl_qw_open_2 = new QToolButton(centralWidget);
        btn_vl_qw_open_2->setObjectName(QStringLiteral("btn_vl_qw_open_2"));
        btn_vl_qw_open_2->setMinimumSize(QSize(45, 0));
        btn_vl_qw_open_2->setFont(font1);

        horizontalLayout_72->addWidget(btn_vl_qw_open_2);


        horizontalLayout_2->addLayout(horizontalLayout_72);

        horizontalLayout_227 = new QHBoxLayout();
        horizontalLayout_227->setSpacing(6);
        horizontalLayout_227->setObjectName(QStringLiteral("horizontalLayout_227"));
        label_235 = new QLabel(centralWidget);
        label_235->setObjectName(QStringLiteral("label_235"));
        label_235->setMaximumSize(QSize(80, 16777215));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        label_235->setFont(font2);

        horizontalLayout_227->addWidget(label_235);

        btn_vl_display_mode_heibai = new QToolButton(centralWidget);
        btn_vl_display_mode_heibai->setObjectName(QStringLiteral("btn_vl_display_mode_heibai"));
        btn_vl_display_mode_heibai->setMinimumSize(QSize(45, 0));
        btn_vl_display_mode_heibai->setFont(font1);

        horizontalLayout_227->addWidget(btn_vl_display_mode_heibai);

        btn_vl_display_mode_caise = new QToolButton(centralWidget);
        btn_vl_display_mode_caise->setObjectName(QStringLiteral("btn_vl_display_mode_caise"));
        btn_vl_display_mode_caise->setMinimumSize(QSize(45, 0));
        btn_vl_display_mode_caise->setFont(font1);

        horizontalLayout_227->addWidget(btn_vl_display_mode_caise);


        horizontalLayout_2->addLayout(horizontalLayout_227);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_229 = new QHBoxLayout();
        horizontalLayout_229->setSpacing(6);
        horizontalLayout_229->setObjectName(QStringLiteral("horizontalLayout_229"));
        label_237 = new QLabel(centralWidget);
        label_237->setObjectName(QStringLiteral("label_237"));
        label_237->setMaximumSize(QSize(80, 16777215));
        label_237->setFont(font2);

        horizontalLayout_229->addWidget(label_237);

        btn_vl_black_target = new QToolButton(centralWidget);
        btn_vl_black_target->setObjectName(QStringLiteral("btn_vl_black_target"));
        btn_vl_black_target->setMinimumSize(QSize(45, 0));
        btn_vl_black_target->setFont(font1);

        horizontalLayout_229->addWidget(btn_vl_black_target);

        btn_vl_write_target = new QToolButton(centralWidget);
        btn_vl_write_target->setObjectName(QStringLiteral("btn_vl_write_target"));
        btn_vl_write_target->setMinimumSize(QSize(45, 0));
        btn_vl_write_target->setFont(font1);

        horizontalLayout_229->addWidget(btn_vl_write_target);


        horizontalLayout_3->addLayout(horizontalLayout_229);

        horizontalLayout_230 = new QHBoxLayout();
        horizontalLayout_230->setSpacing(6);
        horizontalLayout_230->setObjectName(QStringLiteral("horizontalLayout_230"));
        label_238 = new QLabel(centralWidget);
        label_238->setObjectName(QStringLiteral("label_238"));
        label_238->setMaximumSize(QSize(80, 16777215));
        label_238->setFont(font2);

        horizontalLayout_230->addWidget(label_238);

        btn_vl_auto_track = new QToolButton(centralWidget);
        btn_vl_auto_track->setObjectName(QStringLiteral("btn_vl_auto_track"));
        btn_vl_auto_track->setMinimumSize(QSize(45, 0));
        btn_vl_auto_track->setFont(font1);

        horizontalLayout_230->addWidget(btn_vl_auto_track);


        horizontalLayout_3->addLayout(horizontalLayout_230);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_4->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_4);

        txt_vi_send = new QTextEdit(centralWidget);
        txt_vi_send->setObjectName(QStringLiteral("txt_vi_send"));

        verticalLayout->addWidget(txt_vi_send);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(34, 14, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        btn_vi_send = new QPushButton(centralWidget);
        btn_vi_send->setObjectName(QStringLiteral("btn_vi_send"));
        btn_vi_send->setFont(font);

        horizontalLayout_5->addWidget(btn_vi_send);


        verticalLayout->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout, 3, 0, 1, 1);

        fzqjViMoreClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(fzqjViMoreClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 467, 26));
        fzqjViMoreClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(fzqjViMoreClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        fzqjViMoreClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(fzqjViMoreClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        fzqjViMoreClass->setStatusBar(statusBar);

        retranslateUi(fzqjViMoreClass);

        QMetaObject::connectSlotsByName(fzqjViMoreClass);
    } // setupUi

    void retranslateUi(QMainWindow *fzqjViMoreClass)
    {
        fzqjViMoreClass->setWindowTitle(QApplication::translate("fzqjViMoreClass", "\345\217\257\350\247\201\345\205\211\344\270\223\345\256\266\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("fzqjViMoreClass", "\345\217\257\350\247\201\345\205\211\350\260\203\347\204\246\346\250\241\345\274\217", Q_NULLPTR));
        btn_vi_focuse_auto->setText(QApplication::translate("fzqjViMoreClass", "\350\207\252\345\212\250", Q_NULLPTR));
        btn_vi_focuse_manul->setText(QApplication::translate("fzqjViMoreClass", "\346\211\213\345\212\250", Q_NULLPTR));
        btn_vi_focuse_semiAuto->setText(QApplication::translate("fzqjViMoreClass", "\345\215\212\350\207\252\345\212\250", Q_NULLPTR));
        label_52->setText(QApplication::translate("fzqjViMoreClass", "\345\216\273\351\233\276\347\255\211\347\272\247\357\274\232", Q_NULLPTR));
        btn_vl_qw_open_2->setText(QApplication::translate("fzqjViMoreClass", "\350\256\276\347\275\256", Q_NULLPTR));
        label_235->setText(QApplication::translate("fzqjViMoreClass", "\346\230\276\347\244\272\346\250\241\345\274\217\357\274\232", Q_NULLPTR));
        btn_vl_display_mode_heibai->setText(QApplication::translate("fzqjViMoreClass", "\345\244\234\346\231\232", Q_NULLPTR));
        btn_vl_display_mode_caise->setText(QApplication::translate("fzqjViMoreClass", "\347\231\275\345\244\251", Q_NULLPTR));
        label_237->setText(QApplication::translate("fzqjViMoreClass", "\347\233\256\346\240\207\347\211\271\345\276\201\357\274\232", Q_NULLPTR));
        btn_vl_black_target->setText(QApplication::translate("fzqjViMoreClass", "\346\232\227", Q_NULLPTR));
        btn_vl_write_target->setText(QApplication::translate("fzqjViMoreClass", "\344\272\256", Q_NULLPTR));
        label_238->setText(QApplication::translate("fzqjViMoreClass", "\350\207\252\345\212\250\350\267\237\350\270\252\357\274\232", Q_NULLPTR));
        btn_vl_auto_track->setText(QApplication::translate("fzqjViMoreClass", "\345\274\200", Q_NULLPTR));
        label_2->setText(QApplication::translate("fzqjViMoreClass", "\345\217\257\350\247\201\345\205\211\350\207\252\345\256\232\344\271\211\346\214\207\344\273\244", Q_NULLPTR));
        btn_vi_send->setText(QApplication::translate("fzqjViMoreClass", "\344\270\213\345\217\221", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class fzqjViMoreClass: public Ui_fzqjViMoreClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FZQJVIMORE_H
