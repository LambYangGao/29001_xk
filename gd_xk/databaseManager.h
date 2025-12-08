#pragma once

#include <QWidget>
#include "ui_databaseManager.h"
#include "database88002.h"

class databaseManager : public QWidget
{
	Q_OBJECT

public:
	databaseManager(Database88002* database,QWidget*parent = nullptr);
	~databaseManager(void);

	Database88002* m_database = nullptr;

	QDateTime st = QDateTime::currentDateTime().addYears(-10);
	QDateTime ed = QDateTime::currentDateTime();
	//目标
	int targetPageIndx = 1;
	void displayTargets(int pageindx);
	std::vector<Database88002::targetInfo> targets;
	QDateTime m_targetModifyTime;
	//系统错误
	int sysinfoPageIndx = 1;
	void displaySysinfos(int pageindx);
	std::vector<Database88002::sysFaultInfo> sysinfos;
	//系统用户
	int sysUserPageIndx = 1;
	void displaySysUsers(int pageindx);
	std::vector<Database88002::sysUserInfo> users;
	QDateTime m_modifyTime;
	
signals:
	void sig_target_info();
public slots:
	void on_dbmanager_currentChanged(int indx);
	//目标
	void on_pb_target_delete_clicked(void);
	void on_pb_target_pageup_clicked(void);
	void on_pb_target_pagedown_clicked(void);
	void on_pb_target_update_clicked(void);
	void on_pb_target_add_clicked(void);
	void on_pb_targinfo_get_clicked(void);
	void on_pb_target_modify_clicked(void);

	//系统错误
	void on_pb_sysinfo_delete_clicked(void);
	void on_pb_sysinfo_pageup_clicked(void);
	void on_pb_sysinfo_pagedown_clicked(void);
	void on_pb_sysinfo_update_clicked(void);
	//系统用户
	void on_pb_sysuser_delete_clicked(void);
	void on_pb_sysuser_pageup_clicked(void);
	void on_pb_sysuser_pagedown_clicked(void);
	void on_pb_sysuser_update_clicked(void);
	void on_pb_sysuser_add_clicked(void);
	void on_pb_sysuser_get_clicked(void);
	void on_pb_sysuser_modify_clicked(void);

	void on_pb_target_jump_clicked(void);


private:
	Ui::databaseManagerClass ui;
};
