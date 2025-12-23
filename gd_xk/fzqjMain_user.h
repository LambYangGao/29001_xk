#pragma once
#include <QWidget>
#include "ui_fzqjMain_user.h"
#include "h264camera.h"
#include "protocol_picxk.h"
#include "protocol_fk.h"
#include <UdpSocket.h>
#include "myserial.h"
#include "cordtranslib.h"
#include <qmediaplayer.h>
#include <qmediacontent.h>
#include <QGuiApplication>
#include <QWindow>
#include "ConfigManager.h"
#include "PingTest.h"
#include "protocol_yaogan.h"
#include <SF_Stop.h>
#include <opencv2/opencv.hpp>
#include"fzqjGetPicSize.h"
#include"loginfo.h"
#include<qmovie.h>



class fzqjMain_user : public QWidget
{
	Q_OBJECT

public:
	fzqjMain_user(QWidget* parent = Q_NULLPTR);
	~fzqjMain_user(void);

	bool bRecording_VI = false;
	bool bRecording_IR = false;

	//保存日志 
	LogInfo* m_logRealTime = nullptr;
	LogInfo* m_logSelfCheck = nullptr;
	bool m_bSaveRealTimeMsg = false;
	bool m_bSaveSelfCheckMsg = true;

	//配置文件
	ConfigManager* m_configManager;
	XKConfigInfo m_xk_configinfo;
	GDConfigInfo m_gd_configinfo;
	XKDownConfig m_xk_down_config;
private:
	Ui::fzqjMain_user ui;
	//视频网络地址
	QString m_Video_ip = "192.168.0.100";
	QString m_PicIP = "192.168.0.90";
	QString m_Vi_rtsp_path = "rtsp://192.168.0.90:551/vl";//rtsp://192.168.3.90:554/vl rtsp://192.168.3.90:8558/tepStream
	QString m_Ir_rtsp_path = "rtsp://192.168.0.90:552/ir";//rtsp://192.168.3.90:555/ir rtsp://192.168.3.90:8557/tepStream
	int m_VI_port = 10001;//13010
	int m_IR_port = 10002;//13000
	int m_sendPic_port = 10001;
	int m_recvPic_port = 11000;
	int m_recvPic_SelfCheck_port = 12000;
	int m_send_watchdog_port = 54000;
	HEALTH_CTL_MSG m_pic_watch_dog_msg;
	PICUpRealTimeStateMsgStruct m_pic_up_realtime_state;//实时状态
	PICUpSelfCheckStateStruct m_pic_up_selfcheck_state;//自检信息
	RecvBeiDouInfo m_beidou_info;//定位定向信息
	XKDownMsg m_xk_down_msg;
	UdpSocket* m_socket;
	UdpSocket* m_watch_dog_socket;
	int m_watch_dog_recv_port = 51000;
	QMediaPlayer* warningSound;//报警器
	bool isQSoundPlaying = false;
	bool isSoundPlay4Warning = true;
	int is_main_camera = 0;// 0 是可见光 ;1 是红外

	//防控网络地址
	QString m_FK_ip = "192.168.1.6";
	int m_send_FK_heart_port = 35498;//35498
	int m_send_FK_devState_port = 35498;
	int m_send_FK_target_port = 35498;
	int m_Recv_FK_yindao_port = 21000;
	XKUpHeartMsg m_xk_up_heart;//心跳
	XKUpDevStateMsg m_xk_up_devState;//设备状态
	XKUpLogMsg m_xk_up_log;//操作日志

	FKDownGuideMsg m_fk_down_guide;//引导
	FKDownPowerControlMsg m_fk_down_powerControl;//电源控制
	FKDownZTControlMsg m_fk_down_ztCntrol;//转台控制
	FKDownVLControlMsg m_fk_down_vlCntrol;//可见光控制
	FKDownIRControlMsg m_fk_down_irCntrol;//红外控制
	FKDownGDprotectMsg m_fk_down_gdProtect;//大光电保护
	UdpSocket* m_fk_socket;

	MyCordTrans* m_mycordTrans;
	QString timeStrfk;
	QDateTime currentTimefk;
	bool is_send_fk = false;


	//视频参数
	float picLeftPraH = 1080.0;
	float picLeftPraW = 1920.0;
	float picRightPra = (float)1080 / (float)1920;

	//激光测距
	QTimer* m_timer1000 = nullptr;
	bool m_bLaserDisStart = false;
	int dis_start_index = 0;

	QTimer* m_timer500 = nullptr;

	//摇杆
	MySerial* m_serialport = nullptr;
	bool m_serial_isOpen = false;
	bool m_yaogan_isOpen = false;

	protocol_yaogan* m_yaogan;
	bool b_yaogan_mainCamera = false;//false 可见光 true 红外

	int target_manul_type = 0;//手动设置目标类型；0不设置，采信ai上报结果；不为0，按手动设置结果

	//本机经纬高
	double jingdu, weidu, gaodu;
	double beixiang0shidangqianfangweilinshiyonglaixiuzheng = 0;//239013
	double biaojiaoleida_fw = 0;//4.361
	double biaojiaoleida_fy = 0;
	double t_lat_vl, t_log_vl, t_high_vl, t_lat_ir, t_log_ir, t_high_ir;//目标经纬高
	bool isGetLeiDaYinDao = false;

	//伺服预置位
	QList<QString> m_sf_yzw_list;
	bool b_is_sf_cbx_init = false;

	bool b_isFullWindow = false;

	//ping线程
	PingTest* pingFk;
	PingTest* pingPic;
	bool b_pingPic = false;
	bool b_pingFK = false;

	int vi_width;
	int vi_height;
	int ir_width;
	int ir_height;

	bool bRecording = false;
	bool bPrintSelfCheckTime = false;
	double yindao_fw, yindao_fy;
	int desiredPixelCount_ = 3000;

	bool is_adaptive_view = false;

	int gudie_dis;
	float pixe_size_ir = 15 * 0.000001;//15微米像素尺寸
	float pixe_size_vi = 3.9*0.000001;//可见光像素尺寸
	bool is_guideing = false;
	bool is_yindao_send = false;
	int guide_index = 0;
	int last_vi_focus = 0;
	int last_ir_focus = 0;


public:
	void ShowLineText(bool rec_send, QString equi_num, QString txt);//打印字符串
	void sendWatchMsg(void);
	void sendHeartMsg2FK(void);//1hz
	void sendDevStateMsg2FK(void);//1hz
	void sendSFshache(void);
	float degToRad(float deg);
	float radToDeg(float rad);

	void showVL(void);
	void showIR(void);
	QString bool_to_StateInfo(bool in_bool);//状态信息变成中文字符
	QString int8C_to_StateInfo(int8_t in_state);
	QString int8C_to_OpenorClose(int8_t in_state);
	QTimer* m_timer20 = nullptr;//更新定时器
	QTimer* m_timer30000 = nullptr;

	bool is_windows_open(QString str_windows);

	float calculateNewFocalLength(float currentFocalLength, int currentPixelCount, int desiredPixelCount);
	void guideAutoFocus(void);
	void calculateDeltaAngles(
		double u_d, double v_d, // 鼠标点击位置在显示框中的坐标
		double W_d, double H_d, // 显示框的宽高
		double W, double H, // 相机分辨率
		double fov_h, double fov_v, // 相机的水平和垂直视场角（度）
		double theta_0, double phi_0, // 当前方位角和俯仰角（度）
		double& deltaTheta, double& deltaPhi // 输出的跳转角度（度）
	);

	QThread* Vi_H24Decoder_Thread;
	QThread* SDL_Play_vi_Thread;
	QThread* vi_Record_Thread;

	QThread* IR_H24Decoder_Thread;
	QThread* SDL_Play_ir_Thread;
	QThread* Ir_Record_Thread;

	RTSPRecord* vi_Record;
	RTSPRecord* Ir_Record;
	
	QImage* warning_img;
	QMovie* m_warning_gif;

	RTSPDataDecode* Vi_H24Decoder;
	RTSPDataDecode* IR_H24Decoder;

	SDL_Play* SDL_Play_ir;
	SDL_Play* SDL_Play_vi;

	cv::Mat vi_mat;
	cv::Mat ir_mat;


signals:
	void sigUpdateSendBjFwFy(int fw, int fy);
	void sig_RefreshGDConfig(GDConfigInfo m_gd_configinfo);
	void Sig_VI_Record_Start(QString filename);
	void Sig_Ir_Record_Start(QString filename);
	void Sig_Img_Circle(cv::Mat in_mat_vi, cv::Mat in_mat_ir);
	void sig_focal_length_send(int vi_num,int ir_num);
	void sigSendLaserForbidPara(float fw_start, float fw_stop, float fy_start, float fy_stop);
private:
	void UpdateRealTimeState(void);//接收图像板数据后，更新实时状态数据
	void UpdateSelfCheckState(void);//接收图像板数据后，更新自检信息
	void UpdateFKDevState(void);//接收图像板数据后，更新待发送防控目标数据
	void RefreshGDConfig(void);//刷新图像板配置参数
	void InitSFyzw(void);
	void SetBtnHighLight(QWidget* btn, bool flag);//设置按钮高亮
	void SetMainCamera(bool flag);//false 可见光 true 红外
	void SetDevDateTime(void);
	int t_SF_Stop(void);
	//判断是否在禁止区域内
	bool isInNoZone(float current_azimuth, float current_elevation,
		float az_start, float az_end,
		float el_start, float el_end);
	HEALTH_CTL_MSG getWatchDogMsg(int state);
public slots:
	void updateBjFwFy(void);
	void sendMsg2Pic(void);//发送控制指令搭配图像板
	void sendConfig2Pic(void);//修改配置参数
	void InitConfigInfo(void);//初始化系统参数
	void InitConfigBtn(void);//根据参数信息初始化按钮
	void sendMsg2Pic(XKDownMsg xk_down_msg);//发送控制指令搭配图像板
	void sendConfig2Pic(XKDownConfig xk_down_config);//修改配置参数
	void InitConfigInfo(XKConfigInfo xk_configinfo);//初始化系统参数
	void OnRecvData(QByteArray data);//接收图像版数据
	void OnRecvFKData(QByteArray data);//接收防控指令
	void OnTimeOut30000(void);
	void OnTimeOut1000(void);
	void OnTimeOut500(void);
	void OnTimeOut100(void);
	void sendReportMsg(XKUpDevStateMsg in_msg);
	void pingFkRes(bool res);
	void pingPicRes(bool res);
	void sendSFsetV0(void);
	void getFramePara(void);
	void on_btn_clear_recvText_2_clicked(void);
	void updatePixNumAll(void);
	void gdRebootSend(void);
	//激光禁区
	void getLaserForbidPara(void);
	void setLaserForbidPara(float fw_start, float fw_stop, float fy_start, float fy_stop);
	void setSfCompensate(float fw_com, float fy_com);
	void setWatchDog(int state);
protected slots:

	

	//播放区域点击
	void OnScreenClick_VL_left(int x, int y);
	void OnScreenClick_VL_Right(int x, int y);
	void OnScreenClick_IR_left(int x, int y);
	void OnScreenClick_IR_Right(int x, int y);

	//界面功能
	void OncloseToolBtn(void);
	void OnmaximizeToolBtn(void);
	void OnminimizeToolBtn(void);
	void OnImageViewResizeL(void);
	void OnImageViewResizeL(int a, int b);
	void OnImageViewResizeR(void);

	void on_btn_clear_recvText_clicked(void);
	void on_btn_Lidar_YinDao_Focus_clicked(void);
	void on_btn_auto_track_open_clicked(void);
	void on_btn_auto_track_close_clicked(void);
#pragma region
	//可见光
	void on_btn_vl_v_add_pressed(void);//变倍+
	void on_btn_vl_v_add_released(void);
	void vl_zk_stop(void);//指控专用停止（可见光、红外防控的调焦变倍停止都是同一个指令，独起一个打印界面）
	void on_btn_vl_v_add_mini_clicked(void);//微调变倍+
	void on_btn_vl_v_nadd_pressed(void);;//变倍-
	void on_btn_vl_v_nadd_released(void);
	void on_btn_vl_v_nadd_mini_clicked(void);//微调变倍-
	void on_btn_vl_focue_add_pressed(void);//调焦+
	void on_btn_vl_focue_add_released(void);
	void on_btn_vl_focue_add_mini_clicked(void);//调焦微动+
	void on_btn_vl_focuse_minus_pressed(void);//调焦-
	void on_btn_vl_focuse_minus_released(void);
	void on_btn_vl_focuse_minus_mini_clicked(void);//调焦微动-
	void on_btn_vl_auto_focuse_clicked(void);//自动调焦
	void on_btn_vl_dbd_plus_clicked(void);//对比度
	void on_btn_vl_dbd_minus_clicked(void);
	//void on_btn_vl_luma_add_clicked();//亮度
	//void on_btn_vl_luma_nadd_clicked();
	void on_btn_vl_luma_set_clicked(void);
	void btn_vl_qw_open(int level);//去雾
	void on_btn_vl_qw_close_clicked(void);
	void vl_osd_open(void);//十字丝-开
	void vl_osd_close(void);//十字丝-关
	void btn_vl_black_target(void);//是否暗目标
	void btn_vl_write_target(void);
	void vl_display_mode_heibai(void);//黑白
	void vl_display_mode_caise(void);//彩色
	void on_btn_vl_dehaze_open(void);//透雾开
	//void on_btn_vl_dehaze_close();//透雾关

	void on_btn_vl_more_clicked(void);//专家设置
	void vi_focuse_auto(void);//自动调焦
	void vi_focuse_manul(void);//手动调焦
	void vi_focuse_semiAuto(void);//半自动调焦

	void vi_shuiping_on(void);
	void vi_shuiping_off(void);
	void vi_chuizhi_on(void);
	void vi_chuizhi_off(void);


	void vi_send_clicked(QByteArray data);//自定义发送

	void vi_video_stream_update(AVFormatContext* in_FrameContext, AVPacket* in_pkt);
	void vi_img_changed(cv::Mat in_mat);

#pragma endregion

#pragma region
	//红外
	void on_btn_ir_v_add_pressed(void);//变倍+
	void on_btn_ir_v_add_released(void);
	void ir_zk_stop(void);//防控制空指令
	void on_btn_ir_v_add_mini_clicked(void);//微动变倍+
	void on_btn_ir_v_nadd_pressed(void);//变倍-
	void on_btn_ir_v_nadd_released(void);
	void on_btn_ir_v_nadd_mini_clicked(void);//微动变倍-
	void on_btn_ir_focue_add_pressed(void);//调焦+
	void on_btn_ir_focue_add_released(void);
	void on_btn_ir_focue_add_mini_clicked(void);//调焦微动+
	void on_btn_ir_focuse_minus_pressed(void);//调焦-
	void on_btn_ir_focuse_minus_released(void);
	void on_btn_ir_focuse_minus_mini_clicked(void);//调焦微动-

	void pic_improve_open_L(void);//图像增强低
	void pic_improve_open_M(void);//图像增强中
	void pic_improve_open_H(void);//图像增强高
	void pic_improve_close(void);

	void pic_temperature_compensation_open(void); //温度补偿开
	void pic_temperature_compensation_close(void);//温度补偿开

	void pic_focus_speed_L(void);//跟焦速度低 20
	void pic_focus_speed_M(void);//跟焦速度中 70
	void pic_focus_speed_H(void);//跟焦速度高 100

	void on_btn_ir_auto_focuse_clicked(void);//自动调焦

	void on_btn_white_ir_clicked(void);//极性设置
	void on_btn_black_ir_clicked(void);

	void on_btn_ir_osd_open_clicked(void);//十字丝
	void on_btn_ir_osd_close_clicked(void);//

	void on_btn_ir_background_correct_clicked(void);//背景校正
	void ir_manul_correction(void);//红外快门校正

	//void on_btn_ir_set_enhanceType_clicked();//图像增强算法设置
	//void ir_diss_sun_open();//抗阳光开
	//void ir_diss_sun_close();//抗阳光关

	void ir_send_clicked(QByteArray data);//红外自定义指令
	void on_btn_ir_more_clicked(void);//专家设置

	void on_btn_ir_black_target_clicked(void);//是否暗目标
	void on_btn_ir_write_target_clicked(void);

	void ir_video_stream_update(AVFormatContext* in_FrameContext, AVPacket* in_pkt);
	void ir_img_changed(cv::Mat in_mat);
#pragma endregion

#pragma region
	void on_btnMid_pressed(void);//中-刹车
	void on_btnMid_released(void);
	void on_btn_sf_stop_clicked(void);//伺服停止
	void on_btnLT_pressed(void);//左上
	void on_btnLT_released(void);
	void on_btnTop_pressed(void);//上
	void on_btnTop_released(void);
	void on_btnRT_pressed(void);//右上
	void on_btnRT_released(void);
	void on_btnRight_pressed(void);//右
	void on_btnRight_released(void);
	void on_btnRB_pressed(void);//右下
	void on_btnRB_released(void);
	void on_btnBottom_pressed(void);//下
	void on_btnBottom_released(void);
	void on_btnLB_pressed(void);//左下
	void on_btnLB_released(void);
	void on_btnLeft_pressed(void);//左
	void on_btnLeft_released(void);
	void on_Slider_speedx_valueChanged(int value);//方位速度
	void on_Slider_speedy_valueChanged(int value);//俯仰速度
	void sf_close(void);//伺服锁定
	void sf_shuyin(double in_sfx, double in_sfy);//数引
	void on_btn_sf_shuyin_clicked(void);//数引
	void on_btn_sf_fwauto_clicked(void);//方位扫描
	void on_btn_sf_track_clicked(void);//图像跟踪
	void on_btn_sf_exit_track_clicked(void);//退出跟踪
	void on_btn_sf_exit_track_2_clicked(void);
	void on_btn_sf_guizhong_clicked(void);//归中
	void on_btn_sf_shoucang_clicked(void);//收藏
	void on_btn_sf_manual_clicked(void);//手动搜索---作废
	void on_btn_sf_fymanul_clicked(void);//手动俯仰---作废
	void on_btn_sf_more_clicked(void);//更多设置
	void sf_biaojiao_X(void);
	void sf_biaojiao_Y(void);
	void sf_shansao(int fwCenter, int fwNum);
	void sf_zhousao(void);
	void sf_saomiao_info_set(int v, int fytop, int fyL, int fybujin);

	void sf_insert(int num, int fw, int fy);
	void on_btn_sf_insert_clicked(void);
	void sf_toyzw(int num);
	void on_btn_sf_toyzw_clicked(void);//转到预置位

	void on_cbx_sf_yzw_num_editTextChanged(const QString&);


	void sf_delete(int num);

	void sf_biaojiao_any(int fw, int fy);
	void sf_set_fy_bianjie(int fy_H, int fy_L);

	void sf_info_local_altitude(void);
	void sf_info_target_altitude(void);
	void sf_info_target_all(void);

#pragma endregion

#pragma region 激光测距
	void on_btn_open_dis_clicked(void);
	void on_btn_stop_dis_2_clicked(void);
	void on_btn_start_1_dis_2_clicked(void);
	void on_btn_start_more_dis_clicked(void);
#pragma endregion

#pragma region 系统控制
	void on_toolButton_VI_ON_clicked(void);
	void on_toolButton_VI_OFF_clicked(void);
	void on_toolButton_IR_ON_clicked(void);
	void on_toolButton_IR_OFF_clicked(void);
	void on_toolButton_laser_ON_clicked(void);
	void on_toolButton_laser_OFF_clicked(void);

	void on_toolButton_savePic_VL_clicked(void);
	void on_toolButton_savePic_IR_clicked(void);

	void on_toolButton_savevideo_start_clicked(void);
	void on_toolButton_savevideo_stop_clicked(void);

	void on_btn_dsp_open_clicked(void);
	void on_btn_dsp_close_clicked(void);

	void on_btn_ai_open_clicked(void);
	void on_btn_ai_close_clicked(void);

	void on_btn_set_sysinfo_clicked(void);

	//跟踪
	void vl_auto_track(void);
	void vl_all_track(void);
	void on_btn_ir_auto_track_clicked(void);
	void on_btn_ir_all_track_clicked(void);


	void on_btn_selfCheck_clicked(void);//自检
	void on_btn_save_realtimeMsg_clicked(void);//保存实时报文
	void on_btn_save_selfCheckMsg_clicked(void);//保存自检报文

	//rtsp
	void on_btn_vi_video_refresh_clicked(void);
	void on_btn_ir_video_refresh_clicked(void);

	//雷达引导
	void on_btn_devState_Lidar_clicked(void);
	void on_btn_manual_target_send_clicked(void);
#pragma endregion

#pragma region 摇杆
	//小摇杆-串口
	void on_btn_serialport_clicked(void);
	void on_btn_openSerialPort_clicked(void);
	void OnRecvSerialInfo(QByteArray buf);
	//大摇杆-HID
	void on_PosEvent(JoyPosInfoMsg info);//转台移动
	void on_BtnEvent(JoyBtnInfoMsg info);//按钮事件
	void on_PovEvent(bool state);//方位移动
	void on_StateEvent(bool state);//摇杆在线状态
#pragma endregion

#pragma region 计算面积
	void on_btn_CountSize_clicked(void);
#pragma endregion

    void on_btn_SetDevLocation_clicked(void);

};

