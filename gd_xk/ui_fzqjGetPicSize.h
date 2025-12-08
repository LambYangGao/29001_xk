/********************************************************************************
** Form generated from reading UI file 'fzqjGetPicSize.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FZQJGETPICSIZE_H
#define UI_FZQJGETPICSIZE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "RwriteLabel.h"

QT_BEGIN_NAMESPACE

class Ui_fzqjGetPicSizeClass
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    RectLabel *windShowPicVi;
    RectLabel *windShowPicIr;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *editFocusValue;
    QLabel *label_7;
    QLineEdit *editDisValue;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnCount;
    QPushButton *btnImageRefresh;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_8;
    QLineEdit *editWidth;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_9;
    QLineEdit *editHeight;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_10;
    QLineEdit *editSize;

    void setupUi(QWidget *fzqjGetPicSizeClass)
    {
        if (fzqjGetPicSizeClass->objectName().isEmpty())
            fzqjGetPicSizeClass->setObjectName(QStringLiteral("fzqjGetPicSizeClass"));
        fzqjGetPicSizeClass->resize(1155, 456);
        gridLayout = new QGridLayout(fzqjGetPicSizeClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        windShowPicVi = new RectLabel(fzqjGetPicSizeClass);
        windShowPicVi->setObjectName(QStringLiteral("windShowPicVi"));

        horizontalLayout->addWidget(windShowPicVi);

        windShowPicIr = new RectLabel(fzqjGetPicSizeClass);
        windShowPicIr->setObjectName(QStringLiteral("windShowPicIr"));

        horizontalLayout->addWidget(windShowPicIr);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 3);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_6 = new QLabel(fzqjGetPicSizeClass);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_2->addWidget(label_6);

        editFocusValue = new QLineEdit(fzqjGetPicSizeClass);
        editFocusValue->setObjectName(QStringLiteral("editFocusValue"));

        horizontalLayout_2->addWidget(editFocusValue);

        label_7 = new QLabel(fzqjGetPicSizeClass);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_2->addWidget(label_7);

        editDisValue = new QLineEdit(fzqjGetPicSizeClass);
        editDisValue->setObjectName(QStringLiteral("editDisValue"));

        horizontalLayout_2->addWidget(editDisValue);

        horizontalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnCount = new QPushButton(fzqjGetPicSizeClass);
        btnCount->setObjectName(QStringLiteral("btnCount"));

        horizontalLayout_2->addWidget(btnCount);

        btnImageRefresh = new QPushButton(fzqjGetPicSizeClass);
        btnImageRefresh->setObjectName(QStringLiteral("btnImageRefresh"));

        horizontalLayout_2->addWidget(btnImageRefresh);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);
        horizontalLayout_2->setStretch(2, 1);
        horizontalLayout_2->setStretch(3, 2);
        horizontalLayout_2->setStretch(4, 13);
        horizontalLayout_2->setStretch(5, 1);
        horizontalLayout_2->setStretch(6, 1);

        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_8 = new QLabel(fzqjGetPicSizeClass);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_13->addWidget(label_8);

        editWidth = new QLineEdit(fzqjGetPicSizeClass);
        editWidth->setObjectName(QStringLiteral("editWidth"));

        horizontalLayout_13->addWidget(editWidth);

        horizontalLayout_13->setStretch(0, 1);
        horizontalLayout_13->setStretch(1, 3);

        horizontalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_9 = new QLabel(fzqjGetPicSizeClass);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_14->addWidget(label_9);

        editHeight = new QLineEdit(fzqjGetPicSizeClass);
        editHeight->setObjectName(QStringLiteral("editHeight"));

        horizontalLayout_14->addWidget(editHeight);

        horizontalLayout_14->setStretch(0, 1);
        horizontalLayout_14->setStretch(1, 3);

        horizontalLayout_3->addLayout(horizontalLayout_14);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_10 = new QLabel(fzqjGetPicSizeClass);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setTextFormat(Qt::RichText);

        horizontalLayout_15->addWidget(label_10);

        editSize = new QLineEdit(fzqjGetPicSizeClass);
        editSize->setObjectName(QStringLiteral("editSize"));

        horizontalLayout_15->addWidget(editSize);


        horizontalLayout_3->addLayout(horizontalLayout_15);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(2, 3);
        horizontalLayout_3->setStretch(3, 1);

        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        gridLayout->setRowStretch(0, 8);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 1);

        retranslateUi(fzqjGetPicSizeClass);

        QMetaObject::connectSlotsByName(fzqjGetPicSizeClass);
    } // setupUi

    void retranslateUi(QWidget *fzqjGetPicSizeClass)
    {
        fzqjGetPicSizeClass->setWindowTitle(QApplication::translate("fzqjGetPicSizeClass", "\350\256\241\347\256\227", Q_NULLPTR));
        windShowPicVi->setText(QApplication::translate("fzqjGetPicSizeClass", "\346\226\207\345\255\2271", Q_NULLPTR));
        windShowPicIr->setText(QApplication::translate("fzqjGetPicSizeClass", "\346\226\207\345\255\2272", Q_NULLPTR));
        label_6->setText(QApplication::translate("fzqjGetPicSizeClass", "\347\204\246\350\267\235(\346\257\253\347\261\263)\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("fzqjGetPicSizeClass", "\350\267\235\347\246\273(\347\261\263)\357\274\232", Q_NULLPTR));
        btnCount->setText(QApplication::translate("fzqjGetPicSizeClass", "\350\256\241\347\256\227", Q_NULLPTR));
        btnImageRefresh->setText(QApplication::translate("fzqjGetPicSizeClass", "\345\210\267\346\226\260", Q_NULLPTR));
        label_8->setText(QApplication::translate("fzqjGetPicSizeClass", "\345\256\275\345\272\246(\346\257\253\347\261\263)\357\274\232", Q_NULLPTR));
        label_9->setText(QApplication::translate("fzqjGetPicSizeClass", "\351\253\230\345\272\246(\346\257\253\347\261\263)\357\274\232", Q_NULLPTR));
        label_10->setText(QApplication::translate("fzqjGetPicSizeClass", "\351\235\242\347\247\257(\347\261\263)\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class fzqjGetPicSizeClass: public Ui_fzqjGetPicSizeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FZQJGETPICSIZE_H
