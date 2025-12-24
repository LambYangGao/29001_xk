#include "fzqjReport.h"


fzqjReport::fzqjReport(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

fzqjReport::~fzqjReport(void)
{}
void fzqjReport::init_windows(void)
{
	ui.txt_local_lon_value->setText(QString::number((double)manualTarget.Lon / 1000000.0,'f',6));
	ui.txt_local_lat_value->setText(QString::number((double)manualTarget.Lat / 1000000.0, 'f', 6));
	ui.txt_local_alt_value->setText(QString::number((double)manualTarget.Alt / 100.0, 'f', 2));
	ui.cbx_target_type_list->setCurrentIndex((int)manualTarget.targetType);
	ui.txt_target_Az_value->setText(QString::number((double)manualTarget.ztAz/10.0));
	ui.txt_target_pc_value->setText(QString::number((double)((int16_t)manualTarget.ztPc)/10.0));
	ui.txt_target_dis_value->setText(QString::number(manualTarget.targetDis));
}

void fzqjReport::on_btn_report_send_clicked(void)
{
	manualTarget.Lon = ui.txt_local_lon_value->toPlainText().toDouble()* 1000000;
	manualTarget.Lat = ui.txt_local_lat_value->toPlainText().toDouble() * 1000000;
	manualTarget.Alt = ui.txt_local_alt_value->toPlainText().toDouble()*100;
	manualTarget.targetType = ui.cbx_target_type_list->currentIndex();
	manualTarget.ztAz = ui.txt_target_Az_value->toPlainText().toDouble() * 10;
	manualTarget.ztPc = ui.txt_target_pc_value->toPlainText().toDouble() * 10;
	manualTarget.targetDis = ui.txt_target_dis_value->toPlainText().toInt();
	emit sig_report_send(manualTarget);
}