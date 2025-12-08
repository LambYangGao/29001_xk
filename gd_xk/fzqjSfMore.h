#pragma once

#include <QWidget>
#include "ui_fzqjSfMore.h"
#include "cordtranslib.h"

class fzqjSfMore : public QWidget
{
	Q_OBJECT

public:
	fzqjSfMore(QWidget *parent = Q_NULLPTR);
	~fzqjSfMore(void);
	bool isScanInfoSet = false;  // 用于记录是否设置了扫描参数

signals:
	void sig_sf_biaojiao_X(void);
	void sig_sf_biaojiao_Y(void);
	void sig_sf_shansao(int fwCenter, int fwNum);
	void sig_sf_zhousao(void);
	void sig_sf_saomiao_info(int v, int fytop, int fyL,int fybujin);
	void sig_sf_insert(int num, int fw, int fy);
	void sig_sf_toyzw(int num);
	void sig_sf_delete(int num);
	void sig_sf_biaojiao_any(int fw,int fy);
	void sig_sf_set_fy_bianjie(int fy_H, int fy_L);
	void sig_sf_shuyin(double sfx_num, double sfy_num);
	void sig_sf_close(void);
	void sig_sf_local_altitude(void);
	void sig_sf_target_altitude(void);
	void sig_target_info_all(void);
	void sigUpdateBj(void);
	void sigAcquireLaserFobid(void);
	void sigSetLaserForbid(float fw_start, float fw_stop, float fy_start, float fy_stop);
	void sigSFCompensateSet(float fw_compenstae, float fy_compenstate);
	
private:
	Ui::fzqjSfMore ui;
	MyCordTrans* m_mycordTrans;
	void updateEditText(QLineEdit* in_line, QString str);
public slots:
	void on_btn_biaojiao_X_clicked(void);
	void on_btn_biaojiao_Y_clicked(void);
	void on_btn_saomiao_info_clicked(void);
	void on_btn_shansao_clicked(void);
	void on_btn_zhousao_clicked(void);
	void on_btn_insert_clicked(void);
	void on_btn_toyzw_clicked(void);
	void on_btn_delete_clicked(void);
	void on_btn_get_target_zuobiao_clicked(void);
	void on_btn_zhuanhuan_this_clicked(void);
	void on_btn_zhuanhuan_target_clicked(void);
	void on_btn_biaojiao_any_clicked(void);
	void on_btn_set_fy_bianjie_clicked(void);
	void on_btn_sf_shuyin_clicked(void);
	void on_btn_sf_close_clicked(void);
	void on_btn_set_fy_update_clicked(void);
	void SFupdateBjFwFy(int fw, int fy);
	void on_btn_acquire_laser_forbid_clicked(void);
	void on_btn_set_laser_forbid_clicked(void);
	void updateLaserForbid(float fw_start, float fw_stop, float fy_start, float fy_stop);
	void on_btn_sf_compensate_set_clicked(void);
	void on_btn_sf_compensate_default_clicked(void);
};
