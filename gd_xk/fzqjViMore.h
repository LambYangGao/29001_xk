#pragma once

#include <QMainWindow>
#include "ui_fzqjViMore.h"

class fzqjViMore : public QMainWindow
{
	Q_OBJECT

public:
	fzqjViMore(QWidget *parent = nullptr);
	~fzqjViMore(void);
	QByteArray HexStringToByteArray(QString HexString);
signals:
	void sig_vi_focuse_auto();
	void sig_vi_focuse_manul();
	void sig_vi_focuse_semiAuto();
	void sig_vi_send_clicked(QByteArray data);

	void sig_vi_shuiping_on();
	void sig_vi_shuiping_off();
	void sig_vi_chuizhi_on();
	void sig_vi_chuizhi_off();
	void sig_vi_qw_open_2(int level);
	void sig_vl_black_target();
	void sig_vl_write_target();
	void sig_vl_auto_track();
	void sig_vl_all_track();
	void sig_vl_display_mode_heibai();
	void sig_vl_display_mode_caise();
	void sig_vl_osd_open();
	void sig_btn_vl_osd_close();
private:
	Ui::fzqjViMoreClass ui;
public slots:
	
	void on_btn_vi_focuse_auto_clicked(void);
	void on_btn_vi_focuse_manul_clicked(void);
	void on_btn_vi_focuse_semiAuto_clicked(void);
	void on_btn_vi_send_clicked(void);

	void on_btn_vi_shuiping_on_clicked(void);
	void on_btn_vi_shuiping_off_clicked(void);
	void on_btn_vi_chuizhi_on_clicked(void);
	void on_btn_vi_chuizhi_off_clicked(void);
	void on_btn_vl_qw_open_2_clicked(void);
	void on_btn_vl_black_target_clicked(void);
	void on_btn_vl_write_target_clicked(void);
	void on_btn_vl_auto_track_clicked(void);
	void on_btn_vl_all_track_clicked(void);
	void on_btn_vl_display_mode_heibai_clicked(void);
	void on_btn_vl_display_mode_caise_clicked(void);
	void on_btn_vl_osd_open_clicked(void);
	void on_btn_vl_osd_close_clicked(void);
};
