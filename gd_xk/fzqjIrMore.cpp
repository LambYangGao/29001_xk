#include "fzqjIrMore.h"
#include <QMessageBox>
#include <qdebug.h>

fzqjIrMore::fzqjIrMore(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//for (int i = 0; i < ui.horizontalLayout_225->count(); ++i) {
	//	QWidget* w = ui.horizontalLayout_225->itemAt(i)->widget();
	//	if (w != NULL)
	//		w->setVisible(false);
	//}

}

fzqjIrMore::~fzqjIrMore(void)
{}

QByteArray fzqjIrMore::HexStringToByteArray(QString HexString)
{
	bool ok;
	QByteArray ret;
	HexString = HexString.trimmed();
	HexString = HexString.simplified();
	QStringList sl = HexString.split(" ");

	foreach(QString s, sl) {
		if (!s.isEmpty())
		{
			char c = s.toInt(&ok, 16) & 0xFF;
			if (ok) {
				ret.append(c);
			}
			else {
				qDebug() << QStringLiteral("非法的16进制字符：") << s;
				QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("非法的16进制字符: \"%1\"").arg(s));
			}
		}
	}
	return ret;
}
//void fzqjIrMore::on_btn_ir_diss_sun_open_clicked()
//{
//    emit sig_ir_diss_sun_open();
//}
//void fzqjIrMore::on_btn_ir_diss_sun_close_clicked()
//{
//    emit sig_ir_diss_sun_close();
//}
//void fzqjIrMore::on_btn_ir_set_enhanceType_clicked()
//{
//    int enhanceType = ui.cbx_enhanceType->currentIndex();
//    int irEnhanceLvl = ui.txt_irEnhanceLvl->text().toInt();
//    emit sig_ir_set_enhanceType(enhanceType, irEnhanceLvl);
//}
void fzqjIrMore::on_btn_ir_manul_correction_clicked(void)
{
	emit sig_ir_manul_correction();
}
void fzqjIrMore::on_btn_ir_send_clicked(void)
{
	QByteArray data = HexStringToByteArray(ui.txt_ir_send->toPlainText());
	emit sig_ir_send_clicked(data);
}

void fzqjIrMore::on_btn_pic_improve_open_L_clicked(void)
{
	emit sig_pic_improve_open_L();
}

void fzqjIrMore::on_btn_pic_improve_open_M_clicked(void)
{
	emit sig_pic_improve_open_M();
}

void fzqjIrMore::on_btn_pic_improve_open_H_clicked(void)
{
	emit sig_pic_improve_open_H();
}

void fzqjIrMore::on_btn_pic_improve_close_clicked(void)
{
	emit sig_pic_improve_close();
}

void fzqjIrMore::on_btn_ir_auto_focuse_clicked(void)
{
	emit sig_ir_auto_focuse();
}

void fzqjIrMore::on_btn_ir_osd_open_clicked(void)
{
	emit sig_ir_osd_open();
}

void fzqjIrMore::on_btn_ir_osd_close_clicked(void)
{
	emit sig_ir_osd_close();
}

void fzqjIrMore::on_btn_ir_auto_track_clicked(void)
{
	emit sig_ir_auto_track();
}

void fzqjIrMore::on_btn_ir_all_track_clicked(void)
{
	emit sig_ir_all_track();
}

void fzqjIrMore::on_btn_ir_focus_speed_L_clicked(void)
{
	emit sig_ir_focus_speed_L();
}

void fzqjIrMore::on_btn_ir_focus_speed_M_clicked(void)
{
	emit sig_ir_focus_speed_M();
}

void fzqjIrMore::on_btn_ir_focus_speed_H_clicked(void)
{
	emit sig_ir_focus_speed_H();
}

void fzqjIrMore::on_btn_ir_temperature_compensation_open_clicked(void)
{
	emit sig_ir_temperature_compensation_open();
}

void fzqjIrMore::on_btn_ir_temperature_compensation_close_clicked(void)
{
	emit sig_ir_temperature_compensation_close();
}

void fzqjIrMore::on_btn_ir_black_target_2_clicked(void)
{
	emit sig_ir_black_target_2();
}

void fzqjIrMore::on_btn_ir_write_target_2_clicked(void)
{
	emit sig_ir_write_target_2();
}

