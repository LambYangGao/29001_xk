#include "fzqjSfMore.h"
#include <QMessageBox>

fzqjSfMore::fzqjSfMore(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.groupBox_4->hide();
	//ui.groupBox_6->hide();
	QRegExp regExp("-?\\d+(\\.\\d+)?");
	QRegExpValidator* validator = new QRegExpValidator(regExp, this);
	//QLineEdit* lineEdit = new QLineEdit(this);
	//lineEdit->setValidator(validator);
	ui.txt_fw_V->setValidator(new QRegExpValidator(QRegExp("-?\\d+(\\.\\d+)?")));
	ui.txt_fy_top->setValidator(new QRegExpValidator(QRegExp("-?\\d+(\\.\\d+)?")));
	ui.txt_fy_L->setValidator(new QRegExpValidator(QRegExp("-?\\d+(\\.\w\d+)?")));
	ui.txt_fy_bujin->setValidator(new QRegExpValidator(QRegExp("-?\\d+(\\.\\d+)?")));
	ui.txt_fw_center->setValidator(new QRegExpValidator(QRegExp("-?\\d+(\\.\\d+)?")));
	ui.txt_fw_number->setValidator(new QRegExpValidator(QRegExp("-?\\d+(\\.\\d+)?")));

	ui.txt_right_fw->setValidator(new QRegExpValidator(QRegExp("-?\\d+(\\.\\d+)?")));
	ui.txt_right_fy->setValidator(new QRegExpValidator(QRegExp("-?\\d+(\\.\\d+)?")));
	ui.txt_fy_H->setValidator(new QRegExpValidator(QRegExp("-?\\d+(\\.\\d+)?")));
	ui.txt_fy_L_2->setValidator(new QRegExpValidator(QRegExp("-?\\d+(\\.\\d+)?")));
}

fzqjSfMore::~fzqjSfMore(void)
{
	//
}

void fzqjSfMore::on_btn_biaojiao_X_clicked(void)
{
	if (QMessageBox::question(NULL, QStringLiteral("提示"), QStringLiteral("确定执行伺服标校动作？")) == QMessageBox::Yes)
	{
		emit sig_sf_biaojiao_X();
	}
}

void fzqjSfMore::updateEditText(QLineEdit *in_line, QString str)
{
	in_line->setText(str);
}

void fzqjSfMore::on_btn_biaojiao_Y_clicked(void)
{
	if (QMessageBox::question(NULL, QStringLiteral("提示"), QStringLiteral("确定执行伺服标校动作？")) == QMessageBox::Yes)
	{
		emit sig_sf_biaojiao_Y();
	}
}

void fzqjSfMore::on_btn_saomiao_info_clicked(void)
{

	std::vector<QString> emptyFields; // 用于记录空输入框的名称
	std::vector<double> errorDataList;// 判断是否正确数值

	// 获取数值并检查输入框是否为空
	if (ui.txt_fw_V->text().isEmpty())
		emptyFields.push_back("方位速度");
	float f_fw_V = ui.txt_fw_V->text().toFloat();

	if (ui.txt_fy_top->text().isEmpty())
		emptyFields.push_back("俯仰上边界");
	float f_fy_top = ui.txt_fy_top->text().toFloat();

	if (ui.txt_fy_L->text().isEmpty())
		emptyFields.push_back("俯仰下边界");
	float f_fy_L = ui.txt_fy_L->text().toFloat();

	if (ui.txt_fy_bujin->text().isEmpty())
		emptyFields.push_back("俯仰步进");
	float f_fy_bujin = ui.txt_fy_bujin->text().toFloat();

	// 若有空字段，逐一提示
	if (!emptyFields.empty())
	{
		for (int i = 0; i < emptyFields.size(); i++)
		{
			QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("以下字段不能为空: %1").arg(emptyFields[i]));
		}
		isScanInfoSet = false; // 参数无效，不允许进行扇扫
		return;
	}

	// 边界限制
	if (f_fw_V < 0 || f_fw_V > 60)
	{
		errorDataList.push_back(f_fw_V);
	}
	if (f_fy_top < -50 || f_fy_top > 90 || f_fy_top < f_fy_L)
	{
		errorDataList.push_back(f_fy_top);
	}
	if (f_fy_L < -50 || f_fy_L > 90 || f_fy_top < f_fy_L)
	{
		errorDataList.push_back(f_fy_L);
	}
	if (f_fy_bujin < -5 || f_fy_bujin > 5)
	{
		errorDataList.push_back(f_fy_bujin);
	}

	if (errorDataList.size() > 0)
	{
		for (int i = 0; i < errorDataList.size(); i++)
		{
			QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("非法的数值: %1").arg(errorDataList[i]));
		}
		isScanInfoSet = false;  // 参数无效，不允许进行扇扫
		return;
	}

	// 参数设置成功
	isScanInfoSet = true;
	emit sig_sf_saomiao_info(f_fw_V * 100, f_fy_top * 100, f_fy_L * 100, f_fy_bujin * 100);
}

void fzqjSfMore::on_btn_shansao_clicked(void)
{
	// 检查是否设置了扫描参数
	if (!isScanInfoSet)
	{
		QMessageBox::warning(0, QStringLiteral("提示"), QStringLiteral("请先进行扫描参数设置"));
		return;
	}

	std::vector<QString> emptyFields;  // 用于记录空输入框的名称
	std::vector<double> errorDataList; // 判断是否正确数值

	// 获取数值并检查输入框是否为空
	if (ui.txt_fw_center->text().isEmpty())
		emptyFields.push_back("方位中心");
	float f_fw_center = ui.txt_fw_center->text().toFloat();

	if (ui.txt_fw_number->text().isEmpty())
		emptyFields.push_back("方位幅度");
	float f_fw_number = ui.txt_fw_number->text().toFloat();

	// 若有空字段，逐一提示
	if (!emptyFields.empty())
	{
		for (int i = 0; i < emptyFields.size(); i++)
		{
			QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("以下字段不能为空: %1").arg(emptyFields[i]));
		}
		return;
	}

	// 边界限制和循环判断
	if (f_fw_center <= 0 || f_fw_center >= 360)
	{
		errorDataList.push_back(f_fw_center);
	}
	if ((f_fw_center - f_fw_number < 0 && f_fw_center - f_fw_number + 360 < 0) ||
		(f_fw_center + f_fw_number > 360 && f_fw_center + f_fw_number - 360 > 360) ||
		f_fw_number == 0)
	{
		errorDataList.push_back(f_fw_number);
	}

	if (errorDataList.size() > 0)
	{
		for (int i = 0; i < errorDataList.size(); i++)
		{
			QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("非法的数值: %1").arg(errorDataList[i]));
		}
		return;
	}

	emit sig_sf_shansao(f_fw_center * 100, f_fw_number * 100);
}

void fzqjSfMore::on_btn_zhousao_clicked(void)
{
	emit sig_sf_zhousao();
}

void fzqjSfMore::on_btn_insert_clicked(void)
{
	//
}

void fzqjSfMore::on_btn_toyzw_clicked(void)
{
	//
}

void fzqjSfMore::on_btn_delete_clicked(void)
{
	//
}


void fzqjSfMore::on_btn_get_target_zuobiao_clicked(void)
{
	//输入值判断
	std::vector<QString> errorDataList;
	if (ui.txt_this_jingdu->text().isNull() || ui.txt_this_jingdu->text().isEmpty())
	{
		errorDataList.push_back("本机经度");
	}
	if (ui.txt_this_weidu->text().isNull() || ui.txt_this_weidu->text().isEmpty())
	{
		errorDataList.push_back("本机纬度");
	}
	if (ui.txt_this_gaodu->text().isNull() || ui.txt_this_gaodu->text().isEmpty())
	{
		errorDataList.push_back("本机高度");
	}
	if (ui.txt_target_jingdu->text().isNull() || ui.txt_target_jingdu->text().isEmpty())
	{
		errorDataList.push_back("目标经度");
	}
	if (ui.txt_target_weidu->text().isNull() || ui.txt_target_weidu->text().isEmpty())
	{
		errorDataList.push_back("目标纬度");
	}
	if (ui.txt_target_gaodu->text().isNull() || ui.txt_target_gaodu->text().isEmpty())
	{
		errorDataList.push_back("目标高度");
	}
	if (errorDataList.size() > 0)
	{
		for (int i = 0; i < errorDataList.size(); i++)
		{
			QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("非法的数值: \"%1\"").arg(errorDataList[i]));
		}
		return;
	}
	double this_jingdu, this_weidu, this_gaodu;
	double target_jingdu, target_weidu, target_gaodu;
	double target_fw, target_fy, target_dis;
	this_jingdu = ui.txt_this_jingdu->text().toDouble();
	this_weidu = ui.txt_this_weidu->text().toDouble();
	this_gaodu = ui.txt_this_gaodu->text().toDouble();
	target_jingdu = ui.txt_target_jingdu->text().toDouble();
	target_weidu = ui.txt_target_weidu->text().toDouble();
	target_gaodu = ui.txt_target_gaodu->text().toDouble();
	m_mycordTrans->targetGps2TargetPolar(this_weidu, this_jingdu, this_gaodu, target_weidu, target_jingdu, target_gaodu, 0, 0, 0, target_dis, target_fw, target_fy);
	ui.txt_target_fw->setText(QString::number(target_fw, 'f', 3));
	ui.txt_target_fy->setText(QString::number(target_fy, 'f', 3));
	ui.txt_target_dis->setText(QString::number(target_dis, 'f', 3));
	emit sig_target_info_all();
}

void fzqjSfMore::on_btn_zhuanhuan_this_clicked(void)
{
	double jingdu_du, jingdu_fen, jingdu_miao;
	double weidu_du, weidu_fen, weidu_miao;
	double jingdu, weidu;
	jingdu_du = ui.txt_this_jingdu_du->text().toDouble();
	jingdu_fen = ui.txt_this_jingdu_fen->text().toDouble();
	jingdu_miao = ui.txt_this_jingdu_miao->text().toDouble();
	weidu_du = ui.txt_this_weidu_du->text().toDouble();
	weidu_fen = ui.txt_this_weidu_fen->text().toDouble();
	weidu_miao = ui.txt_this_weidu_miao->text().toDouble();
	jingdu = jingdu_du + jingdu_fen / 60.0 + jingdu_miao / 3600.0;
	weidu = weidu_du + weidu_fen / 60.0 + weidu_miao / 3600.0;
	ui.txt_this_jingdu->setText(QString::number(jingdu, 'f', 8));
	ui.txt_this_weidu->setText(QString::number(weidu, 'f', 8));
	emit sig_sf_local_altitude();
}

void fzqjSfMore::on_btn_zhuanhuan_target_clicked(void)
{
	double jingdu_du, jingdu_fen, jingdu_miao;
	double weidu_du, weidu_fen, weidu_miao;
	double jingdu, weidu;
	jingdu_du = ui.txt_target_jingdu_du->text().toDouble();
	jingdu_fen = ui.txt_target_jingdu_fen->text().toDouble();
	jingdu_miao = ui.txt_target_jingdu_miao->text().toDouble();
	weidu_du = ui.txt_target_weidu_du->text().toDouble();
	weidu_fen = ui.txt_target_weidu_fen->text().toDouble();
	weidu_miao = ui.txt_target_weidu_miao->text().toDouble();
	jingdu = jingdu_du + jingdu_fen / 60.0 + jingdu_miao / 3600.0;
	weidu = weidu_du + weidu_fen / 60.0 + weidu_miao / 3600.0;
	ui.txt_target_jingdu->setText(QString::number(jingdu, 'f', 8));
	ui.txt_target_weidu->setText(QString::number(weidu, 'f', 8));
	emit sig_sf_target_altitude();
}

void fzqjSfMore::on_btn_biaojiao_any_clicked(void)
{
	if (QMessageBox::question(NULL, QStringLiteral("提示"), QStringLiteral("确定执行伺服标校动作？")) == QMessageBox::Yes)
	{
		emit sig_sf_biaojiao_any(ui.txt_right_fw->text().toDouble() * 1000, ui.txt_right_fy->text().toDouble() * 1000);
	}
}

void fzqjSfMore::on_btn_set_fy_bianjie_clicked(void)
{
	if (QMessageBox::question(NULL, QStringLiteral("提示"), QStringLiteral("确定更改伺服俯仰柏楠姐？")) == QMessageBox::Yes)
	{
		emit sig_sf_set_fy_bianjie(ui.txt_fy_H->text().toDouble() * 100, ui.txt_fy_H->text().toDouble() * 100);
	}
}

void fzqjSfMore::on_btn_sf_shuyin_clicked(void)
{
	//
}

void fzqjSfMore::on_btn_sf_close_clicked(void)
{
	emit sig_sf_close();
}

void fzqjSfMore::on_btn_set_fy_update_clicked(void)
{
	emit sigUpdateBj();
}

void fzqjSfMore::SFupdateBjFwFy(int fw, int fy)
{
	float fw_f = static_cast<float>(fw) / 1000;
	float fy_f = static_cast<float>(fy) / 1000;
	ui.txt_right_fw->setText(QString::number(fw_f));
	ui.txt_right_fy->setText(QString::number(fy_f));
}

void fzqjSfMore::on_btn_acquire_laser_forbid_clicked(void)
{
	emit sigAcquireLaserFobid();
}

void fzqjSfMore::on_btn_set_laser_forbid_clicked(void)
{
	float fw_start_f = ui.txt_laser_fw_forbid_start->text().toFloat();
	float fw_stop_f = ui.txt_laser_fw_forbid_stop->text().toFloat();
	float fy_start_f = ui.txt_laser_fy_forbid_start->text().toFloat();
	float fy_stop_f = ui.txt_laser_fy_forbid_stop->text().toFloat();
	if (fw_stop_f- fw_start_f<0 || fy_stop_f- fy_start_f<0)
	{
		QMessageBox::information(this, QStringLiteral("错误"), QStringLiteral("输入范围有误"));
		return;
	}
	emit sigSetLaserForbid(fw_start_f, fw_stop_f, fy_start_f, fy_stop_f);
}

void fzqjSfMore::updateLaserForbid(float fw_start, float fw_stop, float fy_start, float fy_stop)
{
	updateEditText(ui.txt_laser_fw_forbid_start, QString::number(fw_start));
	updateEditText(ui.txt_laser_fw_forbid_stop, QString::number(fw_stop));
	updateEditText(ui.txt_laser_fy_forbid_start, QString::number(fy_start));
	updateEditText(ui.txt_laser_fy_forbid_stop, QString::number(fy_stop));

}

void fzqjSfMore::on_btn_sf_compensate_set_clicked(void)
{
	float fw_compenstation = ui.txt_sf_compensate_fw->text().toFloat();
	float fy_compenstation = ui.txt_sf_compensate_fy->text().toFloat();
	emit sigSFCompensateSet(fw_compenstation, fy_compenstation);
}

void fzqjSfMore::on_btn_sf_compensate_default_clicked(void)
{
	emit sigSFCompensateSet(0, 0);
}

