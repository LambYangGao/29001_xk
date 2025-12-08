/********************************************************************************
** Form generated from reading UI file 'databaseManager.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASEMANAGER_H
#define UI_DATABASEMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_databaseManagerClass
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget_dbmanager;
    QWidget *tab;
    QVBoxLayout *verticalLayout_6;
    QLabel *label;
    QTableWidget *tw_targets;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *label_targets_pageindx;
    QLabel *lb_page_maxnum;
    QPushButton *pb_target_jump;
    QPushButton *pb_target_delete;
    QPushButton *pb_target_pageup;
    QPushButton *pb_target_pagedown;
    QPushButton *pb_target_update;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_pageindx_11;
    QLineEdit *le_target_cata;
    QLabel *label_pageindx_12;
    QLineEdit *le_target_fw;
    QLabel *label_pageindx_17;
    QLineEdit *le_target_fy;
    QPushButton *pb_target_add;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_target_cata;
    QLineEdit *le_tagcata_old;
    QLabel *label_pageindx_14;
    QLineEdit *le_targfw_old;
    QLabel *label_pageindx_18;
    QLineEdit *le_targfy_old;
    QPushButton *pb_targinfo_get;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_target_cata_2;
    QLineEdit *le_tagcata_new;
    QLabel *label_pageindx_16;
    QLineEdit *le_targfw_new;
    QLabel *label_pageindx_20;
    QLineEdit *le_targfy_new;
    QPushButton *pb_target_modify;
    QLabel *label_pageindx_19;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tw_sysinfo;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *label_sysfault_pageindx;
    QLabel *label_7;
    QPushButton *pb_sysinfo_delete;
    QPushButton *pb_sysinfo_pageup;
    QPushButton *pb_sysinfo_pagedown;
    QPushButton *pb_sysinfo_update;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *tw_sysuser;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *label_sysusers_pageindx;
    QLabel *label_pageindx_2;
    QPushButton *pb_sysuser_delete;
    QPushButton *pb_sysuser_pageup;
    QPushButton *pb_sysuser_pagedown;
    QPushButton *pb_sysuser_update;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_pageindx_4;
    QLineEdit *le_username;
    QLabel *label_pageindx_5;
    QLineEdit *le_password;
    QPushButton *pb_sysuser_add;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_pageindx_6;
    QLineEdit *le_username_old;
    QLabel *label_pageindx_7;
    QLineEdit *le_password_old;
    QPushButton *pb_sysuser_get;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_pageindx_9;
    QLineEdit *le_username_new;
    QLabel *label_pageindx_8;
    QLineEdit *le_password_new;
    QPushButton *pb_sysuser_modify;
    QLabel *label_pageindx_10;

    void setupUi(QWidget *databaseManagerClass)
    {
        if (databaseManagerClass->objectName().isEmpty())
            databaseManagerClass->setObjectName(QStringLiteral("databaseManagerClass"));
        databaseManagerClass->resize(600, 757);
        databaseManagerClass->setMinimumSize(QSize(600, 600));
        databaseManagerClass->setMaximumSize(QSize(600, 757));
        verticalLayout_5 = new QVBoxLayout(databaseManagerClass);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget_dbmanager = new QTabWidget(databaseManagerClass);
        tabWidget_dbmanager->setObjectName(QStringLiteral("tabWidget_dbmanager"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(10);
        tabWidget_dbmanager->setFont(font);
        tabWidget_dbmanager->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_6 = new QVBoxLayout(tab);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label);

        tw_targets = new QTableWidget(tab);
        if (tw_targets->columnCount() < 4)
            tw_targets->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tw_targets->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tw_targets->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tw_targets->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tw_targets->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (tw_targets->rowCount() < 15)
            tw_targets->setRowCount(15);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(6, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(7, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(8, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(9, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(10, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(11, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(12, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(13, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tw_targets->setVerticalHeaderItem(14, __qtablewidgetitem18);
        tw_targets->setObjectName(QStringLiteral("tw_targets"));
        tw_targets->setAutoFillBackground(false);

        verticalLayout_6->addWidget(tw_targets);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(15, 16777215));

        horizontalLayout->addWidget(label_3);

        label_targets_pageindx = new QLineEdit(tab);
        label_targets_pageindx->setObjectName(QStringLiteral("label_targets_pageindx"));
        label_targets_pageindx->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(label_targets_pageindx);

        lb_page_maxnum = new QLabel(tab);
        lb_page_maxnum->setObjectName(QStringLiteral("lb_page_maxnum"));
        lb_page_maxnum->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(lb_page_maxnum);

        pb_target_jump = new QPushButton(tab);
        pb_target_jump->setObjectName(QStringLiteral("pb_target_jump"));
        pb_target_jump->setMinimumSize(QSize(80, 24));
        pb_target_jump->setMaximumSize(QSize(160, 16777215));

        horizontalLayout->addWidget(pb_target_jump);

        pb_target_delete = new QPushButton(tab);
        pb_target_delete->setObjectName(QStringLiteral("pb_target_delete"));
        pb_target_delete->setMinimumSize(QSize(80, 24));
        pb_target_delete->setMaximumSize(QSize(160, 16777215));

        horizontalLayout->addWidget(pb_target_delete);

        pb_target_pageup = new QPushButton(tab);
        pb_target_pageup->setObjectName(QStringLiteral("pb_target_pageup"));
        pb_target_pageup->setMinimumSize(QSize(80, 24));
        pb_target_pageup->setMaximumSize(QSize(160, 16777215));

        horizontalLayout->addWidget(pb_target_pageup);

        pb_target_pagedown = new QPushButton(tab);
        pb_target_pagedown->setObjectName(QStringLiteral("pb_target_pagedown"));
        pb_target_pagedown->setMinimumSize(QSize(80, 24));
        pb_target_pagedown->setMaximumSize(QSize(160, 16777215));

        horizontalLayout->addWidget(pb_target_pagedown);

        pb_target_update = new QPushButton(tab);
        pb_target_update->setObjectName(QStringLiteral("pb_target_update"));
        pb_target_update->setMinimumSize(QSize(80, 24));
        pb_target_update->setMaximumSize(QSize(160, 16777215));

        horizontalLayout->addWidget(pb_target_update);


        verticalLayout_6->addLayout(horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_pageindx_11 = new QLabel(tab);
        label_pageindx_11->setObjectName(QStringLiteral("label_pageindx_11"));
        label_pageindx_11->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_7->addWidget(label_pageindx_11);

        le_target_cata = new QLineEdit(tab);
        le_target_cata->setObjectName(QStringLiteral("le_target_cata"));
        le_target_cata->setMinimumSize(QSize(50, 0));

        horizontalLayout_7->addWidget(le_target_cata);

        label_pageindx_12 = new QLabel(tab);
        label_pageindx_12->setObjectName(QStringLiteral("label_pageindx_12"));
        label_pageindx_12->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_7->addWidget(label_pageindx_12);

        le_target_fw = new QLineEdit(tab);
        le_target_fw->setObjectName(QStringLiteral("le_target_fw"));
        le_target_fw->setMinimumSize(QSize(50, 0));

        horizontalLayout_7->addWidget(le_target_fw);

        label_pageindx_17 = new QLabel(tab);
        label_pageindx_17->setObjectName(QStringLiteral("label_pageindx_17"));
        label_pageindx_17->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_7->addWidget(label_pageindx_17);

        le_target_fy = new QLineEdit(tab);
        le_target_fy->setObjectName(QStringLiteral("le_target_fy"));
        le_target_fy->setMinimumSize(QSize(50, 0));

        horizontalLayout_7->addWidget(le_target_fy);

        pb_target_add = new QPushButton(tab);
        pb_target_add->setObjectName(QStringLiteral("pb_target_add"));
        pb_target_add->setMinimumSize(QSize(80, 24));
        pb_target_add->setMaximumSize(QSize(160, 16777215));

        horizontalLayout_7->addWidget(pb_target_add);


        verticalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_target_cata = new QLabel(tab);
        label_target_cata->setObjectName(QStringLiteral("label_target_cata"));
        label_target_cata->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_8->addWidget(label_target_cata);

        le_tagcata_old = new QLineEdit(tab);
        le_tagcata_old->setObjectName(QStringLiteral("le_tagcata_old"));
        le_tagcata_old->setMinimumSize(QSize(50, 0));

        horizontalLayout_8->addWidget(le_tagcata_old);

        label_pageindx_14 = new QLabel(tab);
        label_pageindx_14->setObjectName(QStringLiteral("label_pageindx_14"));
        label_pageindx_14->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_8->addWidget(label_pageindx_14);

        le_targfw_old = new QLineEdit(tab);
        le_targfw_old->setObjectName(QStringLiteral("le_targfw_old"));
        le_targfw_old->setMinimumSize(QSize(50, 0));

        horizontalLayout_8->addWidget(le_targfw_old);

        label_pageindx_18 = new QLabel(tab);
        label_pageindx_18->setObjectName(QStringLiteral("label_pageindx_18"));
        label_pageindx_18->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_8->addWidget(label_pageindx_18);

        le_targfy_old = new QLineEdit(tab);
        le_targfy_old->setObjectName(QStringLiteral("le_targfy_old"));
        le_targfy_old->setMinimumSize(QSize(50, 0));

        horizontalLayout_8->addWidget(le_targfy_old);

        pb_targinfo_get = new QPushButton(tab);
        pb_targinfo_get->setObjectName(QStringLiteral("pb_targinfo_get"));
        pb_targinfo_get->setMinimumSize(QSize(80, 24));
        pb_targinfo_get->setMaximumSize(QSize(160, 16777215));

        horizontalLayout_8->addWidget(pb_targinfo_get);


        verticalLayout_6->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_target_cata_2 = new QLabel(tab);
        label_target_cata_2->setObjectName(QStringLiteral("label_target_cata_2"));
        label_target_cata_2->setMinimumSize(QSize(52, 0));
        label_target_cata_2->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_9->addWidget(label_target_cata_2);

        le_tagcata_new = new QLineEdit(tab);
        le_tagcata_new->setObjectName(QStringLiteral("le_tagcata_new"));
        le_tagcata_new->setMinimumSize(QSize(50, 0));
        le_tagcata_new->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_9->addWidget(le_tagcata_new);

        label_pageindx_16 = new QLabel(tab);
        label_pageindx_16->setObjectName(QStringLiteral("label_pageindx_16"));
        label_pageindx_16->setMinimumSize(QSize(20, 0));
        label_pageindx_16->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_9->addWidget(label_pageindx_16);

        le_targfw_new = new QLineEdit(tab);
        le_targfw_new->setObjectName(QStringLiteral("le_targfw_new"));
        le_targfw_new->setMinimumSize(QSize(50, 0));
        le_targfw_new->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_9->addWidget(le_targfw_new);

        label_pageindx_20 = new QLabel(tab);
        label_pageindx_20->setObjectName(QStringLiteral("label_pageindx_20"));
        label_pageindx_20->setMinimumSize(QSize(20, 0));
        label_pageindx_20->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_9->addWidget(label_pageindx_20);

        le_targfy_new = new QLineEdit(tab);
        le_targfy_new->setObjectName(QStringLiteral("le_targfy_new"));
        le_targfy_new->setMinimumSize(QSize(50, 0));
        le_targfy_new->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_9->addWidget(le_targfy_new);

        pb_target_modify = new QPushButton(tab);
        pb_target_modify->setObjectName(QStringLiteral("pb_target_modify"));
        pb_target_modify->setMinimumSize(QSize(80, 24));
        pb_target_modify->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_9->addWidget(pb_target_modify);


        verticalLayout_6->addLayout(horizontalLayout_9);

        label_pageindx_19 = new QLabel(tab);
        label_pageindx_19->setObjectName(QStringLiteral("label_pageindx_19"));
        label_pageindx_19->setMaximumSize(QSize(40, 16777215));

        verticalLayout_6->addWidget(label_pageindx_19);

        tabWidget_dbmanager->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tw_sysinfo = new QTableWidget(tab_2);
        if (tw_sysinfo->columnCount() < 5)
            tw_sysinfo->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tw_sysinfo->setHorizontalHeaderItem(0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tw_sysinfo->setHorizontalHeaderItem(1, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tw_sysinfo->setHorizontalHeaderItem(2, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tw_sysinfo->setHorizontalHeaderItem(3, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tw_sysinfo->setHorizontalHeaderItem(4, __qtablewidgetitem23);
        if (tw_sysinfo->rowCount() < 15)
            tw_sysinfo->setRowCount(15);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(0, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(1, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(2, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(3, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(4, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(5, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(6, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(7, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(8, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(9, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(10, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(11, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(12, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(13, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tw_sysinfo->setVerticalHeaderItem(14, __qtablewidgetitem38);
        tw_sysinfo->setObjectName(QStringLiteral("tw_sysinfo"));

        verticalLayout_2->addWidget(tw_sysinfo);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_2->addWidget(label_4);

        label_sysfault_pageindx = new QLabel(tab_2);
        label_sysfault_pageindx->setObjectName(QStringLiteral("label_sysfault_pageindx"));
        label_sysfault_pageindx->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_2->addWidget(label_sysfault_pageindx);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_2->addWidget(label_7);

        pb_sysinfo_delete = new QPushButton(tab_2);
        pb_sysinfo_delete->setObjectName(QStringLiteral("pb_sysinfo_delete"));
        pb_sysinfo_delete->setEnabled(true);
        pb_sysinfo_delete->setMinimumSize(QSize(80, 24));

        horizontalLayout_2->addWidget(pb_sysinfo_delete);

        pb_sysinfo_pageup = new QPushButton(tab_2);
        pb_sysinfo_pageup->setObjectName(QStringLiteral("pb_sysinfo_pageup"));
        pb_sysinfo_pageup->setMinimumSize(QSize(80, 24));

        horizontalLayout_2->addWidget(pb_sysinfo_pageup);

        pb_sysinfo_pagedown = new QPushButton(tab_2);
        pb_sysinfo_pagedown->setObjectName(QStringLiteral("pb_sysinfo_pagedown"));
        pb_sysinfo_pagedown->setMinimumSize(QSize(80, 24));
        pb_sysinfo_pagedown->setMaximumSize(QSize(160, 16777215));

        horizontalLayout_2->addWidget(pb_sysinfo_pagedown);

        pb_sysinfo_update = new QPushButton(tab_2);
        pb_sysinfo_update->setObjectName(QStringLiteral("pb_sysinfo_update"));
        pb_sysinfo_update->setMinimumSize(QSize(80, 24));
        pb_sysinfo_update->setMaximumSize(QSize(160, 16777215));

        horizontalLayout_2->addWidget(pb_sysinfo_update);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tabWidget_dbmanager->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        verticalLayout_3 = new QVBoxLayout(tab_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tw_sysuser = new QTableWidget(tab_3);
        if (tw_sysuser->columnCount() < 3)
            tw_sysuser->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tw_sysuser->setHorizontalHeaderItem(0, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tw_sysuser->setHorizontalHeaderItem(1, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tw_sysuser->setHorizontalHeaderItem(2, __qtablewidgetitem41);
        if (tw_sysuser->rowCount() < 15)
            tw_sysuser->setRowCount(15);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(0, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(1, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(2, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(3, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(4, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(5, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(6, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(7, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(8, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(9, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(10, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(11, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(12, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(13, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tw_sysuser->setVerticalHeaderItem(14, __qtablewidgetitem56);
        tw_sysuser->setObjectName(QStringLiteral("tw_sysuser"));
        tw_sysuser->setSelectionMode(QAbstractItemView::MultiSelection);
        tw_sysuser->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_3->addWidget(tw_sysuser);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_3->addWidget(label_2);

        label_sysusers_pageindx = new QLabel(tab_3);
        label_sysusers_pageindx->setObjectName(QStringLiteral("label_sysusers_pageindx"));
        label_sysusers_pageindx->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_3->addWidget(label_sysusers_pageindx);

        label_pageindx_2 = new QLabel(tab_3);
        label_pageindx_2->setObjectName(QStringLiteral("label_pageindx_2"));
        label_pageindx_2->setMaximumSize(QSize(20, 16777215));

        horizontalLayout_3->addWidget(label_pageindx_2);

        pb_sysuser_delete = new QPushButton(tab_3);
        pb_sysuser_delete->setObjectName(QStringLiteral("pb_sysuser_delete"));
        pb_sysuser_delete->setEnabled(true);
        pb_sysuser_delete->setMinimumSize(QSize(80, 24));

        horizontalLayout_3->addWidget(pb_sysuser_delete);

        pb_sysuser_pageup = new QPushButton(tab_3);
        pb_sysuser_pageup->setObjectName(QStringLiteral("pb_sysuser_pageup"));
        pb_sysuser_pageup->setMinimumSize(QSize(80, 24));

        horizontalLayout_3->addWidget(pb_sysuser_pageup);

        pb_sysuser_pagedown = new QPushButton(tab_3);
        pb_sysuser_pagedown->setObjectName(QStringLiteral("pb_sysuser_pagedown"));
        pb_sysuser_pagedown->setMinimumSize(QSize(80, 24));
        pb_sysuser_pagedown->setMaximumSize(QSize(160, 16777215));

        horizontalLayout_3->addWidget(pb_sysuser_pagedown);

        pb_sysuser_update = new QPushButton(tab_3);
        pb_sysuser_update->setObjectName(QStringLiteral("pb_sysuser_update"));
        pb_sysuser_update->setMinimumSize(QSize(80, 24));
        pb_sysuser_update->setMaximumSize(QSize(160, 16777215));

        horizontalLayout_3->addWidget(pb_sysuser_update);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_pageindx_4 = new QLabel(tab_3);
        label_pageindx_4->setObjectName(QStringLiteral("label_pageindx_4"));
        label_pageindx_4->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(label_pageindx_4);

        le_username = new QLineEdit(tab_3);
        le_username->setObjectName(QStringLiteral("le_username"));
        le_username->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(le_username);

        label_pageindx_5 = new QLabel(tab_3);
        label_pageindx_5->setObjectName(QStringLiteral("label_pageindx_5"));
        label_pageindx_5->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_4->addWidget(label_pageindx_5);

        le_password = new QLineEdit(tab_3);
        le_password->setObjectName(QStringLiteral("le_password"));
        le_password->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(le_password);

        pb_sysuser_add = new QPushButton(tab_3);
        pb_sysuser_add->setObjectName(QStringLiteral("pb_sysuser_add"));
        pb_sysuser_add->setMinimumSize(QSize(80, 24));
        pb_sysuser_add->setMaximumSize(QSize(160, 16777215));

        horizontalLayout_4->addWidget(pb_sysuser_add);


        verticalLayout_3->addLayout(horizontalLayout_4);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_pageindx_6 = new QLabel(tab_3);
        label_pageindx_6->setObjectName(QStringLiteral("label_pageindx_6"));
        label_pageindx_6->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_5->addWidget(label_pageindx_6);

        le_username_old = new QLineEdit(tab_3);
        le_username_old->setObjectName(QStringLiteral("le_username_old"));
        le_username_old->setMinimumSize(QSize(80, 0));

        horizontalLayout_5->addWidget(le_username_old);

        label_pageindx_7 = new QLabel(tab_3);
        label_pageindx_7->setObjectName(QStringLiteral("label_pageindx_7"));
        label_pageindx_7->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_5->addWidget(label_pageindx_7);

        le_password_old = new QLineEdit(tab_3);
        le_password_old->setObjectName(QStringLiteral("le_password_old"));
        le_password_old->setMinimumSize(QSize(80, 0));

        horizontalLayout_5->addWidget(le_password_old);

        pb_sysuser_get = new QPushButton(tab_3);
        pb_sysuser_get->setObjectName(QStringLiteral("pb_sysuser_get"));
        pb_sysuser_get->setMinimumSize(QSize(80, 24));
        pb_sysuser_get->setMaximumSize(QSize(160, 16777215));

        horizontalLayout_5->addWidget(pb_sysuser_get);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_pageindx_9 = new QLabel(tab_3);
        label_pageindx_9->setObjectName(QStringLiteral("label_pageindx_9"));
        label_pageindx_9->setMinimumSize(QSize(30, 0));
        label_pageindx_9->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_6->addWidget(label_pageindx_9);

        le_username_new = new QLineEdit(tab_3);
        le_username_new->setObjectName(QStringLiteral("le_username_new"));
        le_username_new->setMinimumSize(QSize(80, 0));

        horizontalLayout_6->addWidget(le_username_new);

        label_pageindx_8 = new QLabel(tab_3);
        label_pageindx_8->setObjectName(QStringLiteral("label_pageindx_8"));
        label_pageindx_8->setMinimumSize(QSize(20, 0));
        label_pageindx_8->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_6->addWidget(label_pageindx_8);

        le_password_new = new QLineEdit(tab_3);
        le_password_new->setObjectName(QStringLiteral("le_password_new"));
        le_password_new->setMinimumSize(QSize(80, 0));

        horizontalLayout_6->addWidget(le_password_new);

        pb_sysuser_modify = new QPushButton(tab_3);
        pb_sysuser_modify->setObjectName(QStringLiteral("pb_sysuser_modify"));
        pb_sysuser_modify->setMinimumSize(QSize(80, 24));
        pb_sysuser_modify->setMaximumSize(QSize(160, 16777215));

        horizontalLayout_6->addWidget(pb_sysuser_modify);


        verticalLayout_4->addLayout(horizontalLayout_6);


        verticalLayout_3->addLayout(verticalLayout_4);

        label_pageindx_10 = new QLabel(tab_3);
        label_pageindx_10->setObjectName(QStringLiteral("label_pageindx_10"));
        label_pageindx_10->setMaximumSize(QSize(40, 16777215));

        verticalLayout_3->addWidget(label_pageindx_10);

        tabWidget_dbmanager->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget_dbmanager);


        verticalLayout_5->addLayout(verticalLayout);


        retranslateUi(databaseManagerClass);

        tabWidget_dbmanager->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(databaseManagerClass);
    } // setupUi

    void retranslateUi(QWidget *databaseManagerClass)
    {
        databaseManagerClass->setWindowTitle(QApplication::translate("databaseManagerClass", "databaseManager", Q_NULLPTR));
        label->setText(QApplication::translate("databaseManagerClass", "\346\225\260 \346\215\256 \345\272\223 \347\256\241 \347\220\206", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tw_targets->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("databaseManagerClass", "\346\227\266\351\227\264", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tw_targets->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("databaseManagerClass", "\347\233\256\346\240\207\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tw_targets->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("databaseManagerClass", "\346\226\271\344\275\215\350\247\222", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tw_targets->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("databaseManagerClass", "\344\277\257\344\273\260\350\247\222", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tw_targets->verticalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("databaseManagerClass", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tw_targets->verticalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("databaseManagerClass", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tw_targets->verticalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("databaseManagerClass", "3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tw_targets->verticalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("databaseManagerClass", "4", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tw_targets->verticalHeaderItem(4);
        ___qtablewidgetitem8->setText(QApplication::translate("databaseManagerClass", "5", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = tw_targets->verticalHeaderItem(5);
        ___qtablewidgetitem9->setText(QApplication::translate("databaseManagerClass", "6", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = tw_targets->verticalHeaderItem(6);
        ___qtablewidgetitem10->setText(QApplication::translate("databaseManagerClass", "7", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem11 = tw_targets->verticalHeaderItem(7);
        ___qtablewidgetitem11->setText(QApplication::translate("databaseManagerClass", "8", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem12 = tw_targets->verticalHeaderItem(8);
        ___qtablewidgetitem12->setText(QApplication::translate("databaseManagerClass", "9", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem13 = tw_targets->verticalHeaderItem(9);
        ___qtablewidgetitem13->setText(QApplication::translate("databaseManagerClass", "10", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem14 = tw_targets->verticalHeaderItem(10);
        ___qtablewidgetitem14->setText(QApplication::translate("databaseManagerClass", "11", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem15 = tw_targets->verticalHeaderItem(11);
        ___qtablewidgetitem15->setText(QApplication::translate("databaseManagerClass", "12", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem16 = tw_targets->verticalHeaderItem(12);
        ___qtablewidgetitem16->setText(QApplication::translate("databaseManagerClass", "13", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem17 = tw_targets->verticalHeaderItem(13);
        ___qtablewidgetitem17->setText(QApplication::translate("databaseManagerClass", "14", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem18 = tw_targets->verticalHeaderItem(14);
        ___qtablewidgetitem18->setText(QApplication::translate("databaseManagerClass", "15", Q_NULLPTR));
        label_3->setText(QApplication::translate("databaseManagerClass", "\347\254\254", Q_NULLPTR));
        lb_page_maxnum->setText(QApplication::translate("databaseManagerClass", "\351\241\265", Q_NULLPTR));
        pb_target_jump->setText(QApplication::translate("databaseManagerClass", "\350\267\263\350\275\254", Q_NULLPTR));
        pb_target_delete->setText(QApplication::translate("databaseManagerClass", "\345\210\240\351\231\244", Q_NULLPTR));
        pb_target_pageup->setText(QApplication::translate("databaseManagerClass", "\344\270\212\344\270\200\351\241\265", Q_NULLPTR));
        pb_target_pagedown->setText(QApplication::translate("databaseManagerClass", "\344\270\213\344\270\200\351\241\265", Q_NULLPTR));
        pb_target_update->setText(QApplication::translate("databaseManagerClass", "\346\237\245\350\257\242", Q_NULLPTR));
        label_pageindx_11->setText(QApplication::translate("databaseManagerClass", "\347\233\256\346\240\207\347\261\273\345\236\213", Q_NULLPTR));
        label_pageindx_12->setText(QApplication::translate("databaseManagerClass", "\346\226\271\344\275\215", Q_NULLPTR));
        label_pageindx_17->setText(QApplication::translate("databaseManagerClass", "\344\277\257\344\273\260", Q_NULLPTR));
        pb_target_add->setText(QApplication::translate("databaseManagerClass", "\345\242\236\345\212\240", Q_NULLPTR));
        label_target_cata->setText(QApplication::translate("databaseManagerClass", "\347\233\256\346\240\207\347\261\273\345\236\213", Q_NULLPTR));
        label_pageindx_14->setText(QApplication::translate("databaseManagerClass", "\346\226\271\344\275\215", Q_NULLPTR));
        label_pageindx_18->setText(QApplication::translate("databaseManagerClass", "\344\277\257\344\273\260", Q_NULLPTR));
        pb_targinfo_get->setText(QApplication::translate("databaseManagerClass", "\350\216\267\345\217\226", Q_NULLPTR));
        label_target_cata_2->setText(QString());
        label_pageindx_16->setText(QString());
        label_pageindx_20->setText(QString());
        pb_target_modify->setText(QApplication::translate("databaseManagerClass", "\344\277\256\346\224\271", Q_NULLPTR));
        label_pageindx_19->setText(QString());
        tabWidget_dbmanager->setTabText(tabWidget_dbmanager->indexOf(tab), QApplication::translate("databaseManagerClass", "\347\233\256\346\240\207\347\256\241\347\220\206", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem19 = tw_sysinfo->horizontalHeaderItem(0);
        ___qtablewidgetitem19->setText(QApplication::translate("databaseManagerClass", "\346\227\266\351\227\264", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem20 = tw_sysinfo->horizontalHeaderItem(1);
        ___qtablewidgetitem20->setText(QApplication::translate("databaseManagerClass", "\347\272\242\345\244\226", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem21 = tw_sysinfo->horizontalHeaderItem(2);
        ___qtablewidgetitem21->setText(QApplication::translate("databaseManagerClass", "\345\217\257\350\247\201\345\205\211", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem22 = tw_sysinfo->horizontalHeaderItem(3);
        ___qtablewidgetitem22->setText(QApplication::translate("databaseManagerClass", "\346\277\200\345\205\211\346\265\213\350\267\235", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem23 = tw_sysinfo->horizontalHeaderItem(4);
        ___qtablewidgetitem23->setText(QApplication::translate("databaseManagerClass", "\344\274\272\346\234\215", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem24 = tw_sysinfo->verticalHeaderItem(0);
        ___qtablewidgetitem24->setText(QApplication::translate("databaseManagerClass", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem25 = tw_sysinfo->verticalHeaderItem(1);
        ___qtablewidgetitem25->setText(QApplication::translate("databaseManagerClass", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem26 = tw_sysinfo->verticalHeaderItem(2);
        ___qtablewidgetitem26->setText(QApplication::translate("databaseManagerClass", "3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem27 = tw_sysinfo->verticalHeaderItem(3);
        ___qtablewidgetitem27->setText(QApplication::translate("databaseManagerClass", "4", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem28 = tw_sysinfo->verticalHeaderItem(4);
        ___qtablewidgetitem28->setText(QApplication::translate("databaseManagerClass", "5", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem29 = tw_sysinfo->verticalHeaderItem(5);
        ___qtablewidgetitem29->setText(QApplication::translate("databaseManagerClass", "6", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem30 = tw_sysinfo->verticalHeaderItem(6);
        ___qtablewidgetitem30->setText(QApplication::translate("databaseManagerClass", "7", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem31 = tw_sysinfo->verticalHeaderItem(7);
        ___qtablewidgetitem31->setText(QApplication::translate("databaseManagerClass", "8", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem32 = tw_sysinfo->verticalHeaderItem(8);
        ___qtablewidgetitem32->setText(QApplication::translate("databaseManagerClass", "9", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem33 = tw_sysinfo->verticalHeaderItem(9);
        ___qtablewidgetitem33->setText(QApplication::translate("databaseManagerClass", "10", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem34 = tw_sysinfo->verticalHeaderItem(10);
        ___qtablewidgetitem34->setText(QApplication::translate("databaseManagerClass", "11", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem35 = tw_sysinfo->verticalHeaderItem(11);
        ___qtablewidgetitem35->setText(QApplication::translate("databaseManagerClass", "12", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem36 = tw_sysinfo->verticalHeaderItem(12);
        ___qtablewidgetitem36->setText(QApplication::translate("databaseManagerClass", "13", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem37 = tw_sysinfo->verticalHeaderItem(13);
        ___qtablewidgetitem37->setText(QApplication::translate("databaseManagerClass", "14", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem38 = tw_sysinfo->verticalHeaderItem(14);
        ___qtablewidgetitem38->setText(QApplication::translate("databaseManagerClass", "15", Q_NULLPTR));
        label_4->setText(QApplication::translate("databaseManagerClass", "\347\254\254", Q_NULLPTR));
        label_sysfault_pageindx->setText(QString());
        label_7->setText(QApplication::translate("databaseManagerClass", "\347\254\254", Q_NULLPTR));
        pb_sysinfo_delete->setText(QApplication::translate("databaseManagerClass", "\345\210\240\351\231\244", Q_NULLPTR));
        pb_sysinfo_pageup->setText(QApplication::translate("databaseManagerClass", "\344\270\212\344\270\200\351\241\265", Q_NULLPTR));
        pb_sysinfo_pagedown->setText(QApplication::translate("databaseManagerClass", "\344\270\213\344\270\200\351\241\265", Q_NULLPTR));
        pb_sysinfo_update->setText(QApplication::translate("databaseManagerClass", "\345\210\267\346\226\260", Q_NULLPTR));
        tabWidget_dbmanager->setTabText(tabWidget_dbmanager->indexOf(tab_2), QApplication::translate("databaseManagerClass", "\347\263\273\347\273\237\344\277\241\346\201\257", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem39 = tw_sysuser->horizontalHeaderItem(0);
        ___qtablewidgetitem39->setText(QApplication::translate("databaseManagerClass", "\346\227\266\351\227\264", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem40 = tw_sysuser->horizontalHeaderItem(1);
        ___qtablewidgetitem40->setText(QApplication::translate("databaseManagerClass", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem41 = tw_sysuser->horizontalHeaderItem(2);
        ___qtablewidgetitem41->setText(QApplication::translate("databaseManagerClass", "\345\257\206\347\240\201", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem42 = tw_sysuser->verticalHeaderItem(0);
        ___qtablewidgetitem42->setText(QApplication::translate("databaseManagerClass", "1", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem43 = tw_sysuser->verticalHeaderItem(1);
        ___qtablewidgetitem43->setText(QApplication::translate("databaseManagerClass", "2", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem44 = tw_sysuser->verticalHeaderItem(2);
        ___qtablewidgetitem44->setText(QApplication::translate("databaseManagerClass", "3", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem45 = tw_sysuser->verticalHeaderItem(3);
        ___qtablewidgetitem45->setText(QApplication::translate("databaseManagerClass", "4", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem46 = tw_sysuser->verticalHeaderItem(4);
        ___qtablewidgetitem46->setText(QApplication::translate("databaseManagerClass", "5", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem47 = tw_sysuser->verticalHeaderItem(5);
        ___qtablewidgetitem47->setText(QApplication::translate("databaseManagerClass", "6", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem48 = tw_sysuser->verticalHeaderItem(6);
        ___qtablewidgetitem48->setText(QApplication::translate("databaseManagerClass", "7", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem49 = tw_sysuser->verticalHeaderItem(7);
        ___qtablewidgetitem49->setText(QApplication::translate("databaseManagerClass", "8", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem50 = tw_sysuser->verticalHeaderItem(8);
        ___qtablewidgetitem50->setText(QApplication::translate("databaseManagerClass", "9", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem51 = tw_sysuser->verticalHeaderItem(9);
        ___qtablewidgetitem51->setText(QApplication::translate("databaseManagerClass", "10", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem52 = tw_sysuser->verticalHeaderItem(10);
        ___qtablewidgetitem52->setText(QApplication::translate("databaseManagerClass", "11", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem53 = tw_sysuser->verticalHeaderItem(11);
        ___qtablewidgetitem53->setText(QApplication::translate("databaseManagerClass", "12", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem54 = tw_sysuser->verticalHeaderItem(12);
        ___qtablewidgetitem54->setText(QApplication::translate("databaseManagerClass", "13", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem55 = tw_sysuser->verticalHeaderItem(13);
        ___qtablewidgetitem55->setText(QApplication::translate("databaseManagerClass", "14", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem56 = tw_sysuser->verticalHeaderItem(14);
        ___qtablewidgetitem56->setText(QApplication::translate("databaseManagerClass", "15", Q_NULLPTR));
        label_2->setText(QApplication::translate("databaseManagerClass", "\347\254\254", Q_NULLPTR));
        label_sysusers_pageindx->setText(QString());
        label_pageindx_2->setText(QApplication::translate("databaseManagerClass", "\351\241\265", Q_NULLPTR));
        pb_sysuser_delete->setText(QApplication::translate("databaseManagerClass", "\345\210\240\351\231\244", Q_NULLPTR));
        pb_sysuser_pageup->setText(QApplication::translate("databaseManagerClass", "\344\270\212\344\270\200\351\241\265", Q_NULLPTR));
        pb_sysuser_pagedown->setText(QApplication::translate("databaseManagerClass", "\344\270\213\344\270\200\351\241\265", Q_NULLPTR));
        pb_sysuser_update->setText(QApplication::translate("databaseManagerClass", "\345\210\267\346\226\260", Q_NULLPTR));
        label_pageindx_4->setText(QApplication::translate("databaseManagerClass", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_pageindx_5->setText(QApplication::translate("databaseManagerClass", "\345\257\206\347\240\201", Q_NULLPTR));
        pb_sysuser_add->setText(QApplication::translate("databaseManagerClass", "\345\242\236\345\212\240", Q_NULLPTR));
        label_pageindx_6->setText(QApplication::translate("databaseManagerClass", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_pageindx_7->setText(QApplication::translate("databaseManagerClass", "\345\257\206\347\240\201", Q_NULLPTR));
        pb_sysuser_get->setText(QApplication::translate("databaseManagerClass", "\350\216\267\345\217\226", Q_NULLPTR));
        label_pageindx_9->setText(QString());
        label_pageindx_8->setText(QString());
        pb_sysuser_modify->setText(QApplication::translate("databaseManagerClass", "\344\277\256\346\224\271", Q_NULLPTR));
        label_pageindx_10->setText(QString());
        tabWidget_dbmanager->setTabText(tabWidget_dbmanager->indexOf(tab_3), QApplication::translate("databaseManagerClass", "\347\263\273\347\273\237\347\224\250\346\210\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class databaseManagerClass: public Ui_databaseManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASEMANAGER_H
