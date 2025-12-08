#pragma once

#include <QMainWindow>
#include "ui_fzqjIrMore.h"

class fzqjIrMore : public QMainWindow
{
	Q_OBJECT

public:
	fzqjIrMore(QWidget* parent = nullptr);
	~fzqjIrMore(void);
	QByteArray HexStringToByteArray(QString HexString);
signals:
	void sig_ir_diss_sun_open();
	void sig_ir_diss_sun_close();
	void sig_ir_set_enhanceType(int type, int level);
	void sig_ir_manul_correction();
	void sig_ir_send_clicked(QByteArray data);
	void sig_pic_improve_open_L();
	void sig_pic_improve_open_M();
	void sig_pic_improve_open_H();
	void sig_pic_improve_close();
	void sig_ir_auto_focuse();
	void sig_ir_osd_open();
	void sig_ir_osd_close();
	void sig_ir_auto_track();
	void sig_ir_all_track();
	void sig_ir_black_target_2();
	void sig_ir_write_target_2();
	void sig_ir_temperature_compensation_open();
	void sig_ir_temperature_compensation_close();
	void sig_ir_focus_speed_L();
	void sig_ir_focus_speed_M();
	void sig_ir_focus_speed_H();

private:
	Ui::fzqjIrMoreClass ui;
public slots:
	//void on_btn_ir_diss_sun_open_clicked();
	//void on_btn_ir_diss_sun_close_clicked();
	//void on_btn_ir_set_enhanceType_clicked();
	void on_btn_ir_manul_correction_clicked(void);
	void on_btn_ir_send_clicked(void);
	void on_btn_pic_improve_open_L_clicked(void);
	void on_btn_pic_improve_open_M_clicked(void);
	void on_btn_pic_improve_open_H_clicked(void);
	void on_btn_pic_improve_close_clicked(void);
	void on_btn_ir_auto_focuse_clicked(void);
	void on_btn_ir_osd_open_clicked(void);
	void on_btn_ir_osd_close_clicked(void);
	void on_btn_ir_auto_track_clicked(void);
	void on_btn_ir_all_track_clicked(void);
	void on_btn_ir_focus_speed_L_clicked(void);
	void on_btn_ir_focus_speed_M_clicked(void);
	void on_btn_ir_focus_speed_H_clicked(void);
	void on_btn_ir_temperature_compensation_open_clicked(void);
	void on_btn_ir_temperature_compensation_close_clicked(void);
	void on_btn_ir_black_target_2_clicked(void);
	void on_btn_ir_write_target_2_clicked(void);


};
