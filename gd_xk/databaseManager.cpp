#include "databaseManager.h"
#include<qtabwidget.h>
#include<QModelIndexList>
#include <algorithm>

databaseManager::databaseManager(Database88002* database, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.tabWidget_dbmanager, SIGNAL(currentChanged(int)), this, SLOT(on_dbmanager_currentChanged(int)));
	ui.tabWidget_dbmanager->removeTab(1);
	ui.tabWidget_dbmanager->removeTab(1);
	m_database = database;

	on_pb_target_update_clicked();
}

databaseManager::~databaseManager(void)
{

}


//系统用户显示
void databaseManager::displaySysUsers(int pageindx)
{
	ui.tw_sysuser->clearContents();

	int stindx = (pageindx - 1) * 15;
	int endindx = pageindx * 15;
	if (endindx > users.size())
	{
		endindx = users.size();
	}

	for (int i = stindx; i < endindx; i++)
	{
		QString un = users[i].userName;
		QDateTime ut = users[i].time;
		QString ps = users[i].password;

		ui.tw_sysuser->setItem(i % 15, 0, new QTableWidgetItem(ut.toString("yyyy-MM-dd HH:mm:ss")));
		ui.tw_sysuser->setItem(i % 15, 1, new QTableWidgetItem(un));
		ui.tw_sysuser->setItem(i % 15, 2, new QTableWidgetItem(ps));

	};
}
//系统用户删除
void databaseManager::on_pb_sysuser_delete_clicked(void)
{
	QModelIndexList selectedrows;
	selectedrows = ui.tw_sysuser->selectionModel()->selectedIndexes();
	std::vector<int>selrows;
	for (int i = 0; i < selectedrows.count(); i++)
	{
		int rindx = selectedrows.at(i).row();
		rindx = (sysUserPageIndx - 1) * 15 + rindx;
		selrows.push_back(rindx);
	}
	std::sort(selrows.begin(), selrows.end());
	selrows.erase(std::unique(selrows.begin(), selrows.end()), selrows.end());

	for (int i = selrows.size() - 1; i >= 0; i--)
	{
		int indx = selrows[i];
		if (indx > (users.size() - 1))
		{
			continue;
		}
		QString username = users[indx].userName;
		QDateTime usertime = users[indx].time;
		m_database->clearSysUser(usertime, username);
	}

	std::vector<Database88002::sysUserInfo>().swap(users);
	ed = QDateTime::currentDateTime();
	m_database->querySysUser(st, ed, users);

	displaySysUsers(sysUserPageIndx);
	ui.label_sysusers_pageindx->setText(QStringLiteral(" %1").arg(sysUserPageIndx));

}
//系统用户上一页
void databaseManager::on_pb_sysuser_pageup_clicked(void)
{
	sysUserPageIndx -= 1;
	if (sysUserPageIndx < 1)
	{
		sysUserPageIndx = 1;
	}

	displaySysUsers(sysUserPageIndx);
	ui.label_sysusers_pageindx->setText(QStringLiteral(" %1").arg(sysUserPageIndx));
}
//系统用户下一页
void databaseManager::on_pb_sysuser_pagedown_clicked(void)
{

	int userNum = users.size();

	int pages = userNum / 15;
	if (userNum > pages * 15)
	{
		pages += 1;
	}

	sysUserPageIndx += 1;

	if (sysUserPageIndx > pages)
	{
		sysUserPageIndx = pages;
	}

	displaySysUsers(sysUserPageIndx);
	ui.label_sysusers_pageindx->setText(QStringLiteral(" %1").arg(sysUserPageIndx));

}
//系统用户刷新
void databaseManager::on_pb_sysuser_update_clicked(void)
{
	std::vector<Database88002::sysUserInfo>().swap(users);
	ed = QDateTime::currentDateTime();
	m_database->querySysUser(st, ed, users);

	displaySysUsers(sysUserPageIndx);
	ui.label_sysusers_pageindx->setText(QStringLiteral(" %1").arg(sysUserPageIndx));
}

void databaseManager::on_pb_sysuser_add_clicked(void)
{
	QDateTime qdt = QDateTime::currentDateTime();
	QString username = ui.le_username->text();
	QString passw = ui.le_password->text();
	m_database->insertSysUser(qdt, username, passw, 0);
	on_pb_sysuser_update_clicked();
}

void databaseManager::on_pb_sysuser_get_clicked(void)
{
	QModelIndexList selectedrows;
	selectedrows = ui.tw_sysuser->selectionModel()->selectedIndexes();
	std::vector<int>selrows;
	for (int i = 0; i < selectedrows.count(); i++)
	{
		int rindx = selectedrows.at(i).row();
		rindx = (sysUserPageIndx - 1) * 15 + rindx;
		selrows.push_back(rindx);
	}
	std::sort(selrows.begin(), selrows.end());
	selrows.erase(std::unique(selrows.begin(), selrows.end()), selrows.end());

	QString passw = users[selrows[0]].password;
	QString username = users[selrows[0]].userName;
	m_modifyTime = users[selrows[0]].time;
	ui.le_username_old->setText(username);
	ui.le_password_old->setText(passw);
}

void databaseManager::on_pb_sysuser_modify_clicked(void)
{

	QString passw = ui.le_password_old->text();
	QString username = ui.le_username_old->text();
	QDateTime usertime = m_modifyTime;
	ui.le_username_old->setText(username);
	ui.le_password_old->setText(passw);

	QString passw_new = ui.le_password_new->text();
	QString username_new = ui.le_username_new->text();

	m_database->modifySysUser(usertime, username, username_new, passw, passw_new, 0, 0);
}

void databaseManager::on_pb_target_jump_clicked(void)
{
	int targetNum = targets.size();

	int pages = targetNum / 15;
	if (targetNum > pages * 15)
	{
		pages += 1;
	}

	int num = ui.label_targets_pageindx->text().toInt();
	if (num > pages)
	{
		num = pages;
		QString numStr = QString::number(num);
		ui.label_targets_pageindx->setText(numStr);
	}
	targetPageIndx = num;
	displayTargets(targetPageIndx);


}

//目标显示
void databaseManager::displayTargets(int pageindx)
{
	int targetNum = targets.size();

	int pages = targetNum / 15;
	if (targetNum > pages * 15)
	{
		pages += 1;
	}
	ui.lb_page_maxnum->setText(QStringLiteral("%1/页").arg(pages));

	ui.tw_targets->clearContents();

	int stindx = (pageindx - 1) * 15;
	int endindx = pageindx * 15;
	if (endindx > targets.size())
	{
		endindx = targets.size();
	}

	for (int i = stindx; i < endindx; i++)
	{

		QDateTime targt = targets[i].time;
		QString targCategory = targets[i].category;
		float targHorizontal = targets[i].horizontal;
		float targVertical = targets[i].vertical;


		ui.tw_targets->setItem(i % 15, 0, new QTableWidgetItem(targt.toString("yyyy-MM-dd HH:mm:ss")));
		ui.tw_targets->setItem(i % 15, 1, new QTableWidgetItem(targCategory));
		ui.tw_targets->setItem(i % 15, 2, new QTableWidgetItem(QStringLiteral("%1").arg(targHorizontal)));
		ui.tw_targets->setItem(i % 15, 3, new QTableWidgetItem(QStringLiteral("%1").arg(targVertical)));

	};
}
//目标删除
void databaseManager::on_pb_target_delete_clicked(void)
{
	QModelIndexList selectedrows;
	selectedrows = ui.tw_targets->selectionModel()->selectedIndexes();
	std::vector<int>selrows;
	for (int i = 0; i < selectedrows.count(); i++)
	{
		int rindx = selectedrows.at(i).row();
		rindx = (targetPageIndx - 1) * 15 + rindx;
		selrows.push_back(rindx);
	}
	std::sort(selrows.begin(), selrows.end());
	selrows.erase(std::unique(selrows.begin(), selrows.end()), selrows.end());

	for (int i = selrows.size() - 1; i >= 0; i--)
	{
		int indx = selrows[i];
		if (indx > (targets.size() - 1))
		{
			continue;
		}

		QDateTime targtime = targets[indx].time;
		QString targcategory = targets[indx].category;
		float targhorizontal = targets[indx].horizontal;
		float targvertical = targets[indx].vertical;

		m_database->clearTargets(targtime, targcategory, targhorizontal, targvertical);
	}

	std::vector<Database88002::targetInfo>().swap(targets);
	ed = QDateTime::currentDateTime();
	m_database->queryTargets(st, ed, targets);
	reverse(targets.begin(), targets.end());

	displayTargets(targetPageIndx);
	ui.label_targets_pageindx->setText(QStringLiteral(" %1").arg(targetPageIndx));
};
//目标上一页
void databaseManager::on_pb_target_pageup_clicked(void)
{
	targetPageIndx -= 1;
	if (targetPageIndx < 1)
	{
		targetPageIndx = 1;
	}

	displayTargets(targetPageIndx);
	ui.label_targets_pageindx->setText(QStringLiteral(" %1").arg(targetPageIndx));
};
//目标下一页
void databaseManager::on_pb_target_pagedown_clicked(void)
{
	int targetNum = targets.size();

	int pages = targetNum / 15;
	if (targetNum > pages * 15)
	{
		pages += 1;
	}

	targetPageIndx += 1;

	if (targetPageIndx > pages)
	{
		targetPageIndx = pages;
	}

	displayTargets(targetPageIndx);
	ui.label_targets_pageindx->setText(QStringLiteral(" %1").arg(targetPageIndx));
}
void databaseManager::on_pb_target_update_clicked(void)
{

	std::vector<Database88002::targetInfo>().swap(targets);
	ed = QDateTime::currentDateTime();
	m_database->queryTargets(st, ed, targets);
	reverse(targets.begin(), targets.end());

	displayTargets(targetPageIndx);
	ui.label_targets_pageindx->setText(QStringLiteral(" %1").arg(targetPageIndx));
	emit sig_target_info();
}
;
//系统信息显示
void databaseManager::displaySysinfos(int pageindx)
{
	ui.tw_sysinfo->clearContents();

	int stindx = (pageindx - 1) * 15;
	int endindx = pageindx * 15;
	if (endindx > sysinfos.size())
		endindx = sysinfos.size();

	for (int i = stindx; i < endindx; i++)
	{

		QDateTime sysinfot = sysinfos[i].time;
		QString sysinfoir = sysinfos[i].ir;
		QString sysinfovl = sysinfos[i].vl;
		QString sysinfolsdet = sysinfos[i].laserDet;
		QString sysinfosd = sysinfos[i].sd;


		ui.tw_sysinfo->setItem(i % 15, 0, new QTableWidgetItem(sysinfot.toString("yyyy-MM-dd HH:mm:ss")));
		ui.tw_sysinfo->setItem(i % 15, 1, new QTableWidgetItem(sysinfoir));
		ui.tw_sysinfo->setItem(i % 15, 2, new QTableWidgetItem(sysinfovl));
		ui.tw_sysinfo->setItem(i % 15, 3, new QTableWidgetItem(sysinfolsdet));
		ui.tw_sysinfo->setItem(i % 15, 4, new QTableWidgetItem(sysinfosd));
	};
};
//系统信息删除
void databaseManager::on_pb_sysinfo_delete_clicked(void)
{
	QModelIndexList selectedrows;
	selectedrows = ui.tw_sysinfo->selectionModel()->selectedIndexes();
	std::vector<int>selrows;
	for (int i = 0; i < selectedrows.count(); i++)
	{
		int rindx = selectedrows.at(i).row();
		rindx = (sysinfoPageIndx - 1) * 15 + rindx;
		selrows.push_back(rindx);
	}
	std::sort(selrows.begin(), selrows.end());
	selrows.erase(std::unique(selrows.begin(), selrows.end()), selrows.end());

	for (int i = selrows.size() - 1; i >= 0; i--)
	{
		int indx = selrows[i];
		if (indx > (sysinfos.size() - 1))
		{
			continue;
		}
		QDateTime targtime = sysinfos[indx].time;
		QString sysinfoir = sysinfos[indx].ir;
		QString sysinfovl = sysinfos[indx].vl;
		QString sysinfolsdet = sysinfos[indx].laserDet;
		QString sysinfosd = sysinfos[indx].sd;

		m_database->clearSysfault(targtime, sysinfoir, sysinfovl, sysinfolsdet, sysinfosd);
	}

	std::vector<Database88002::sysFaultInfo>().swap(sysinfos);
	ed = QDateTime::currentDateTime();
	m_database->querySysfault(st, ed, sysinfos);

	displaySysinfos(sysinfoPageIndx);
	ui.label_sysfault_pageindx->setText(QStringLiteral(" %1").arg(sysinfoPageIndx));

};
//系统信息上一页
void databaseManager::on_pb_sysinfo_pageup_clicked(void)
{
	sysinfoPageIndx -= 1;
	if (sysinfoPageIndx < 1)
	{
		sysinfoPageIndx = 1;
	}

	displaySysinfos(sysinfoPageIndx);
	ui.label_sysfault_pageindx->setText(QStringLiteral(" %1").arg(sysinfoPageIndx));
};
//系统信息下一页
void databaseManager::on_pb_sysinfo_pagedown_clicked(void)
{
	int sysinfoNum = sysinfos.size();

	int pages = sysinfoNum / 15;
	if (sysinfoNum > pages * 15)
	{
		pages += 1;
	}

	sysinfoPageIndx += 1;

	if (sysinfoPageIndx > pages)
		sysinfoPageIndx = pages;

	displaySysinfos(sysinfoPageIndx);
	ui.label_sysfault_pageindx->setText(QStringLiteral(" %1").arg(sysinfoPageIndx));
}
//系统信息刷新
void databaseManager::on_pb_sysinfo_update_clicked(void)
{
	std::vector<Database88002::sysFaultInfo>().swap(sysinfos);
	ed = QDateTime::currentDateTime();
	m_database->querySysfault(st, ed, sysinfos);

	displaySysinfos(sysinfoPageIndx);
	ui.label_sysfault_pageindx->setText(QStringLiteral(" %1").arg(sysinfoPageIndx));
}
void databaseManager::on_pb_target_add_clicked(void)
{
	QDateTime qdt = QDateTime::currentDateTime();
	QString targcata = ui.le_target_cata->text();
	float targfw = ui.le_target_fw->text().toFloat();
	float targfy = ui.le_target_fy->text().toFloat();
	m_database->insertTargets(qdt, targcata, targfw, targfy);
	on_pb_target_update_clicked();
}
void databaseManager::on_pb_targinfo_get_clicked(void)
{
	QModelIndexList selectedrows;
	selectedrows = ui.tw_targets->selectionModel()->selectedIndexes();
	std::vector<int>selrows;
	for (int i = 0; i < selectedrows.count(); i++)
	{
		int rindx = selectedrows.at(i).row();
		rindx = (targetPageIndx - 1) * 15 + rindx;
		selrows.push_back(rindx);
	}
	std::sort(selrows.begin(), selrows.end());
	selrows.erase(std::unique(selrows.begin(), selrows.end()), selrows.end());
	if (selrows.size() == 0)
	{
		return;
	}
	QString cataold = targets[selrows[0]].category;
	QString fwold = QString::number(targets[selrows[0]].horizontal);
	QString fyold = QString::number(targets[selrows[0]].vertical);
	m_targetModifyTime = targets[selrows[0]].time;
	ui.le_tagcata_old->setText(cataold);
	ui.le_targfw_old->setText(fwold);
	ui.le_targfy_old->setText(fyold);


}
void databaseManager::on_pb_target_modify_clicked(void)
{
	QString targcata = ui.le_tagcata_new->text();
	float targfw = ui.le_targfw_new->text().toFloat();
	float targfy = ui.le_targfy_new->text().toFloat();

	QString targcataold = ui.le_tagcata_old->text();
	float targfwold = ui.le_targfw_old->text().toFloat();
	float targfyold = ui.le_targfy_old->text().toFloat();;



	m_database->modifyTargets(m_targetModifyTime, targcataold, targcata, targfwold, targfw, targfyold, targfy);
	on_pb_target_update_clicked();
}
;

void databaseManager::on_dbmanager_currentChanged(int indx)
{
	if (indx == 0)//目标
	{
		std::vector<Database88002::targetInfo>().swap(targets);
		ed = QDateTime::currentDateTime();
		m_database->queryTargets(st, ed, targets);
		reverse(targets.begin(), targets.end());

		displayTargets(targetPageIndx);
		ui.label_targets_pageindx->setText(QStringLiteral(" %1").arg(targetPageIndx));

	}
	if (indx == 1)//系统错误
	{
		std::vector<Database88002::sysFaultInfo>().swap(sysinfos);
		ed = QDateTime::currentDateTime();
		m_database->querySysfault(st, ed, sysinfos);

		displaySysinfos(sysinfoPageIndx);
		ui.label_sysfault_pageindx->setText(QStringLiteral(" %1").arg(sysinfoPageIndx));
	}
	if (indx == 2)//系统用户
	{
		std::vector<Database88002::sysUserInfo>().swap(users);
		ed = QDateTime::currentDateTime();
		m_database->querySysUser(st, ed, users);

		displaySysUsers(sysUserPageIndx);
		ui.label_sysusers_pageindx->setText(QStringLiteral(" %1").arg(sysUserPageIndx));


	}
}
