#pragma once

#include <QMainWindow>
#include "ui_fzqjSysInfo.h"
#include "protocol_picxk.h"
#include "ConfigManager.h"
#include <QFileDialog>
#include<QMessageBox>



class fzqjSysInfo : public QMainWindow
{
	Q_OBJECT

public:
	fzqjSysInfo(QWidget *parent = nullptr);
	~fzqjSysInfo();

	XKDownConfig m_xk_down_config;
	XKDownMsg m_xk_down_msg;
	XKConfigInfo m_xk_configinfo;
	ConfigManager* m_configManager;
	bool fzqjSysInfo::is_ip_ture(QString in_ip);
	void txtToConfig(QLineEdit *in_line,QString in_url);
signals:
	void sig_sendConfig2Pic(XKDownConfig xk_down_config);
	void sig_sendMsg2Pic(XKDownMsg xk_down_msg);
	void sig_InitConfigInfo(XKConfigInfo xk_configinfo);
	void sigUpdatepixnums(void);
	void sigReboot(void);
	//0 重启 1开启自动重启  2关闭自动重启 3杀死程序
	void sigWatchDogMsg(int state);
private:
	Ui::fzqjSysInfoClass ui;
	
public slots:
	void on_btn_getXKInfo_2_clicked(void);
	void on_btn_recv_GD_Port_2_clicked(void);
	void on_btn_send_GD_Port_2_clicked(void);
	void on_btn_recv_ZK_Port_2_clicked(void);
	void on_btn_send_ZK_Port_2_clicked(void);
	void on_btn_GD_IP_2_clicked(void);
	void on_btn_ZK_IP_2_clicked(void);
	void on_btn_XK_IP_2_clicked(void);
	void on_btn_VI_video_addr_2_clicked(void);
	void on_btn_IR_video_addr_2_clicked(void);
	void on_btn_pic_save_path_2_clicked(void);
	void on_btn_video_save_path_2_clicked(void);
	void on_btn_log_save_path_2_clicked(void);
	void on_btn_sound_warning_2_clicked(void);
	void on_btn_DEV_ID_2_clicked(void);
	void on_btn_SOURCE_ID_2_clicked(void);
	void on_btn_getGDInfo_2_clicked(void);
	void on_btn_GD_recv_XK_Port_2_clicked(void);
	void on_btn_GD_send_XK_Port_2_clicked(void);
	void on_btn_GD_GD_IP_2_clicked(void);
	void on_btn_GD_XK_IP_2_clicked(void);
	void on_btn_GD_VI_OSD_2_clicked(void);
	void on_btn_GD_IR_OSD_2_clicked(void);
	void on_btn_GD_VI_threshold_2_clicked(void);
	void on_btn_GD_IR_threshold_2_clicked(void);
	void on_btn_open_pic_save_path_2_clicked(void);
	void on_btn_open_video_save_path_2_clicked(void);
	void on_btn_open_log_save_path_2_clicked(void);
	void on_btn_adaptive_view_clicked(void);
	void on_btn_adaptive_view_piex_vi_clicked(void);
	void on_btn_adaptive_view_piex_ir_clicked(void);

	void on_btn_guidance_adaptive_size_clicked(void);
	void on_btn_guidance_adaptive_pixe_vi_clicked(void);
	void on_btn_guidance_adaptive_pixe_ir_clicked(void);
	void on_btn_guidance_adaptive_clicked(void);
	void on_btn_GD_Reboot_clicked(void);

	void RefreshGDConfig(GDConfigInfo m_gd_configinfo);
	void on_btn_watch_dog_reboot_clicked(void);
	void on_btn_watch_dog_auto_reboot_start_clicked(void);
	void on_btn_watch_dog_auto_reboot_stop_clicked(void);
	void on_btn_watch_dog_stop_clicked(void);
};
