#include "fzqjViMore.h"
#include <QMessageBox>
#include <qdebug.h>


fzqjViMore::fzqjViMore(QWidget* parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);
}

fzqjViMore::~fzqjViMore(void)
{
	this->close();
}

QByteArray fzqjViMore::HexStringToByteArray(QString HexString)
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

void fzqjViMore::on_btn_vi_focuse_auto_clicked(void)
{
	emit sig_vi_focuse_auto();
}

void fzqjViMore::on_btn_vi_focuse_manul_clicked(void)
{
	emit sig_vi_focuse_manul();
}

void fzqjViMore::on_btn_vi_focuse_semiAuto_clicked(void)
{
	emit sig_vi_focuse_semiAuto();
}

void fzqjViMore::on_btn_vi_send_clicked(void)
{
	QByteArray data = HexStringToByteArray(ui.txt_vi_send->toPlainText());
	emit sig_vi_send_clicked(data);
}

void fzqjViMore::on_btn_vi_shuiping_on_clicked(void)
{
	emit sig_vi_shuiping_on();
}

void fzqjViMore::on_btn_vi_shuiping_off_clicked(void)
{
	emit sig_vi_shuiping_off();
}

void fzqjViMore::on_btn_vi_chuizhi_on_clicked(void)
{
	emit sig_vi_chuizhi_on();
}

void fzqjViMore::on_btn_vi_chuizhi_off_clicked(void)
{
	emit sig_vi_chuizhi_off();
}

void fzqjViMore::on_btn_vl_qw_open_2_clicked(void)
{
	emit sig_vi_qw_open_2(ui.spinbox_qw_level_2->value());
}

void fzqjViMore::on_btn_vl_black_target_clicked(void)
{
	emit sig_vl_black_target();
}
void fzqjViMore::on_btn_vl_write_target_clicked(void)
{
	emit sig_vl_write_target();
}

void fzqjViMore::on_btn_vl_auto_track_clicked(void)
{
	emit sig_vl_auto_track();
}

void fzqjViMore::on_btn_vl_all_track_clicked(void)
{
	emit sig_vl_all_track();
}

void fzqjViMore::on_btn_vl_display_mode_heibai_clicked(void)
{
	emit sig_vl_display_mode_heibai();
}

void fzqjViMore::on_btn_vl_display_mode_caise_clicked(void)
{
	emit sig_vl_display_mode_caise();
}

void fzqjViMore::on_btn_vl_osd_open_clicked(void)
{
	emit sig_vl_osd_open();
}

void fzqjViMore::on_btn_vl_osd_close_clicked(void)
{
	emit sig_btn_vl_osd_close();
}
