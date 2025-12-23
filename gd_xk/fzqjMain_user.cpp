#include "fzqjMain_user.h"
#include <Windows.h>
#include "QSimpleLed.h"
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QProcess>
#include <fzqjSfMore.h>
#include <fzqjViMore.h>
#include <fzqjIrMore.h>
#include <QMediaPlaylist>
#include <regex>
#include "fzqjSysInfo.h"
#include "fzqjReport.h"


fzqjMain_user::fzqjMain_user(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	showFullScreen();

	//与设备通信
	init_xk_down_msg(&m_xk_down_msg);
	init_pic_up_realtime_msg(&m_pic_up_realtime_state);
	init_pic_up_selfcheck_msg(&m_pic_up_selfcheck_state);

	//与防控通信

	init_xk_up_heart_msg(&m_xk_up_heart);
	init_xk_up_devState_msg(&m_xk_up_devState);
	init_xk_up_log_msg(&m_xk_up_log);

	//配置文件初始化
	m_configManager = new ConfigManager("Config.ini");
	m_configManager->print();
	init_XKConfigInfo(m_configManager, &m_xk_configinfo);
	InitConfigInfo();
	
	b_is_sf_cbx_init = true;
	InitSFyzw();

	

	m_socket = new UdpSocket(m_recvPic_port);
	m_socket->startThread();//开启socket线程
	connect(m_socket, SIGNAL(sig_hasPendingDatagram(QByteArray)), this, SLOT(OnRecvData(QByteArray)));
	

	m_fk_socket = new UdpSocket(m_Recv_FK_yindao_port);
	m_fk_socket->startThread();//开启socket线程
	connect(m_fk_socket, SIGNAL(sig_hasPendingDatagram(QByteArray)), this, SLOT(OnRecvFKData(QByteArray)));
	m_mycordTrans = new MyCordTrans();

	//播放框-缩放
	connect(ui.label_videodisplay_vl, SIGNAL(MouseLeftClick(int, int)), this, SLOT(OnScreenClick_VL_left(int, int)));
	connect(ui.label_videodisplay_vl, SIGNAL(MouseRightClick(int, int)), this, SLOT(OnScreenClick_VL_Right(int, int)));
	connect(ui.label_videodisplay_ir, SIGNAL(MouseLeftClick(int, int)), this, SLOT(OnScreenClick_IR_left(int, int)));
	connect(ui.label_videodisplay_ir, SIGNAL(MouseRightClick(int, int)), this, SLOT(OnScreenClick_IR_Right(int, int)));
	//OnImageViewResizeL();


	QString file = QCoreApplication::applicationDirPath() + QStringLiteral("/warning.mp3");
	QMediaPlaylist* playlist = new QMediaPlaylist(this);
	warningSound = new QMediaPlayer(this);
	QMediaContent mediaContent= QUrl::fromLocalFile(file);
	//warningSound->setMedia(mediaContent);
	playlist->addMedia(QUrl::fromLocalFile(file));
	playlist->setPlaybackMode(QMediaPlaylist::Loop);
	
	warningSound->setPlaylist(playlist);
	warningSound->setVolume(50);
	//warningSound->play();


	//日志
	string RealStr = m_xk_configinfo.LOG_SAVE_Addr;
	string SelfStr = m_xk_configinfo.LOG_SAVE_Addr;
	RealStr.append("\\LOG_REALTIME");
	SelfStr.append("\\LOG_SELFCHECK");
	m_logRealTime = new LogInfo(1024 * 10, RealStr);
	m_logSelfCheck = new LogInfo(1024 * 10, SelfStr);
	m_logSelfCheck->start();


	//界面-右上角
	connect(ui.closeToolBtn, SIGNAL(clicked()), this, SLOT(OncloseToolBtn()));
	connect(ui.maximizeToolBtn, SIGNAL(clicked()), this, SLOT(OnmaximizeToolBtn()));
	connect(ui.minimizeToolBtn, SIGNAL(clicked()), this, SLOT(OnminimizeToolBtn()));

	//定时器
	m_timer1000 = new QTimer();
	connect(m_timer1000, SIGNAL(timeout()), this, SLOT(OnTimeOut1000()));
	m_timer1000->setInterval(1000);
	m_timer1000->start();

	m_timer30000 = new QTimer();
	connect(m_timer30000, SIGNAL(timeout()), this, SLOT(OnTimeOut30000()));
	m_timer30000->setInterval(30000);
	m_timer30000->start();

	//定时器
	m_timer500 = new QTimer();
	connect(m_timer500, SIGNAL(timeout()), this, SLOT(OnTimeOut500()));
	m_timer500->setInterval(500);


	//ping test
	pingFk = new PingTest(m_FK_ip);
	pingPic = new PingTest(m_PicIP);
	connect(pingFk, SIGNAL(sig_pingResult(bool)), this, SLOT(pingFkRes(bool)));
	connect(pingPic, SIGNAL(sig_pingResult(bool)), this, SLOT(pingPicRes(bool)));
	pingFk->start();
	pingPic->start();

	//开机自检
	//on_btn_selfCheck_clicked();

	//模拟初始化-状态灯
	ui.label_videodisplay_ir->setVisible(true);
	ui.label_videodisplay_vl->setVisible(true);
	ui.label_vi->mColor = QSimpleLed::GREY;
	ui.label_ir->mColor = QSimpleLed::GREY;
	ui.label_SJK->mColor = QSimpleLed::GREY;
	ui.label_cj->mColor = QSimpleLed::GREY;
	ui.label_sf->mColor = QSimpleLed::GREY;
	ui.label_BG->mColor = QSimpleLed::GREY;

	QTimer::singleShot(100, this, SLOT(getFramePara()));
	InitConfigBtn();

	
}



fzqjMain_user::~fzqjMain_user(void)
{
	m_logRealTime->stop();
	m_logSelfCheck->stop();
}

static QTime currecttime;
void fzqjMain_user::ShowLineText(bool rec_send, QString equi_num, QString txt)
{
	ui.textBrowser_2->moveCursor(QTextCursor::End);
	currecttime = QTime::currentTime();
	QString str = QStringLiteral("%1:%2-%3-%4\r\n").arg(currecttime.toString("hh:mm:ss.zzz")).arg(rec_send ? QStringLiteral("收") : QStringLiteral("发")).arg(equi_num).arg(txt);
	ui.textBrowser_2->insertPlainText(str);
	ui.textBrowser_2->moveCursor(QTextCursor::End);
}

void fzqjMain_user::sendWatchMsg(void)
{
	QByteArray buffer;
	buffer.resize(sizeof(HEALTH_CTL_MSG));
	memcpy(buffer.data(), &m_pic_watch_dog_msg, sizeof(HEALTH_CTL_MSG));
	m_socket->SendDatagram(buffer, QHostAddress(m_PicIP), m_send_watchdog_port);
}

void fzqjMain_user::updateBjFwFy(void)
{
	if (isGetLeiDaYinDao == true)
	{
		if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
		{
			int diff_fw = yindao_fw - m_pic_up_realtime_state.fw;
			int diff_fy = yindao_fy - m_pic_up_realtime_state.fy;
			emit sigUpdateSendBjFwFy(diff_fw, diff_fy);
		}
		else
		{
			QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("未在跟踪状态"));
		}
	}
	else
	{
		QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("未开启引导"));

	}
}
void fzqjMain_user::sendMsg2Pic(void)
{
	QByteArray buffer;
	buffer.resize(sizeof(XKDownMsg));
	memcpy(buffer.data(), &m_xk_down_msg, sizeof(XKDownMsg));
	m_socket->SendDatagram(buffer, QHostAddress(m_PicIP), m_sendPic_port);
}

void fzqjMain_user::sendConfig2Pic(void)
{
	QByteArray buffer;
	buffer.resize(sizeof(XKDownConfig));
	memcpy(buffer.data(), &m_xk_down_config, sizeof(XKDownConfig));
	m_socket->SendDatagram(buffer, QHostAddress(m_PicIP), m_sendPic_port);
}

void fzqjMain_user::sendHeartMsg2FK(void)
{
	QByteArray buffer;
	buffer.resize(sizeof(XKUpHeartMsg));
	memcpy(buffer.data(), &m_xk_up_heart, sizeof(XKUpHeartMsg));
	m_socket->SendDatagram(buffer, QHostAddress(m_FK_ip), m_send_FK_heart_port);
}

void fzqjMain_user::sendDevStateMsg2FK(void)
{
	currentTimefk = QDateTime::currentDateTime();
	timeStrfk = currentTimefk.toString("yyyy-MM-dd hh:mm:ss");
	is_send_fk = true;
	//uint16_t curtime_m = timeStrfk.mid(14,2).toUInt();
	//uint16_t curtime_s = timeStrfk.mid(17,2).toUInt();
	//m_xk_up_devState.targetAz = curtime_m;
	//m_xk_up_devState.targetPc = curtime_s;
	QByteArray buffer;
	buffer.resize(sizeof(XKUpDevStateMsg));
	memcpy(buffer.data(), &m_xk_up_devState, sizeof(XKUpDevStateMsg));
	//cout << "m_xk_up_devState.pixel_nums:" << m_xk_up_devState.pixel_nums;
	m_socket->SendDatagram(buffer, QHostAddress(m_FK_ip), m_send_FK_heart_port);
}

void fzqjMain_user::sendSFsetV0(void)
{
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = 0;
	m_xk_down_msg.param_2 = 0;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_SF_STOP;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::sendSFshache(void)
{
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = 0;
	m_xk_down_msg.param_2 = 0;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;

	on_btn_sf_stop_clicked();
}

void fzqjMain_user::getLaserForbidPara(void)
{
	emit sigSendLaserForbidPara(m_xk_configinfo.laser_forbid_fw_start, m_xk_configinfo.laser_forbid_fw_stop,
		m_xk_configinfo.laser_forbid_fy_start, m_xk_configinfo.laser_forbid_fy_stop);
}
void fzqjMain_user::setLaserForbidPara(float fw_start, float fw_stop, float fy_start, float fy_stop)
{
	m_xk_configinfo.laser_forbid_fw_start = fw_start;
	m_xk_configinfo.laser_forbid_fw_stop = fw_stop;
	m_xk_configinfo.laser_forbid_fy_start = fy_start;
	m_xk_configinfo.laser_forbid_fy_stop = fy_stop;
	m_configManager->set("LASER_FORBID_FW_START", QString::number(m_xk_configinfo.laser_forbid_fw_start).toStdString());
	m_configManager->set("LASER_FORBID_FW_STOP", QString::number(m_xk_configinfo.laser_forbid_fw_stop).toStdString());
	m_configManager->set("LASER_FORBID_FY_START", QString::number(m_xk_configinfo.laser_forbid_fy_start).toStdString());
	m_configManager->set("LASER_FORBID_FY_STOP", QString::number(m_xk_configinfo.laser_forbid_fy_stop).toStdString());
	m_configManager->print("Config.ini");
}
void fzqjMain_user::setSfCompensate(float fw_com, float fy_com)
{
	int32_t para1 = (int32_t)(fw_com * 1000);
	int32_t para2 = (int32_t)(fy_com * 1000);
	m_xk_down_msg.msg_type = E_FK_SF_COMPALATE;
	m_xk_down_msg.param_1 = para1;
	m_xk_down_msg.param_2 = para2;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}
void fzqjMain_user::setWatchDog(int state)
{
	m_pic_watch_dog_msg =getWatchDogMsg(state);
	sendWatchMsg();

}
void fzqjMain_user::getFramePara(void)
{
	vi_width = ui.label_videodisplay_vl->width();
	vi_height = ui.label_videodisplay_vl->height();
	ir_width = ui.label_videodisplay_ir->width();
	ir_height = ui.label_videodisplay_ir->height();

	//视频
	showVL();
	showIR();

}

void fzqjMain_user::on_btn_clear_recvText_2_clicked(void)
{
	QString fileName = QDate::currentDate().toString("yyyy-MM-dd") + "_" + QTime::currentTime().toString("hh-mm-ss") + "_ui_control" + ".txt";
	QString filePath = m_xk_configinfo.LOG_SAVE_Addr;
	filePath.append("/LOG_Control_");
	filePath.append(fileName);
	QFile file(filePath);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream out(&file);
		out << ui.textBrowser_2->toPlainText();
		file.close();

	}
}

void fzqjMain_user::updatePixNumAll(void)
{
	/*m_xk_configinfo.IS_GUIDE_ADAPT_VIEW = m_configManager->read("IS_GUIDE_ADAPT_VIEW", 0);*/
	m_xk_configinfo.GUIDE_ADPAT_VIEW_PIXE_VI = m_configManager->read("GUIDE_ADPAT_VIEW_PIXE_VI", 0);
	m_xk_configinfo.GUIDE_ADPAT_VIEW_PIXE_IR = m_configManager->read("GUIDE_ADPAT_VIEW_PIXE_IR", 0);
	m_xk_configinfo.GUIDE_ADPAT_VIEW_SIZE = m_configManager->read("GUIDE_ADPAT_VIEW_SIZE", 0);
}

void fzqjMain_user::gdRebootSend(void)
{
	m_xk_down_msg.msg_type = E_FK_REBOOT;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::showVL(void)
{
	QString vi_url = m_Vi_rtsp_path;
	Vi_H24Decoder_Thread = new QThread();
	Vi_H24Decoder = new RTSPDataDecode("vi", vi_url);
	Vi_H24Decoder->moveToThread(Vi_H24Decoder_Thread);
	connect(Vi_H24Decoder_Thread, &QThread::started, Vi_H24Decoder, &RTSPDataDecode::start);
	connect(Vi_H24Decoder_Thread, &QThread::finished, Vi_H24Decoder, &QObject::deleteLater);
	connect(Vi_H24Decoder_Thread, &QThread::finished, Vi_H24Decoder_Thread, &QThread::deleteLater);
	Vi_H24Decoder_Thread->start();

	SDL_Play_vi_Thread = new QThread();
	SDL_Play_vi = new SDL_Play(vi_width, vi_height, "vi", (void*)ui.label_videodisplay_vl->winId());
	SDL_Play_vi->moveToThread(SDL_Play_vi_Thread);
	connect(SDL_Play_vi_Thread, &QThread::started, SDL_Play_vi, &SDL_Play::start);
	connect(SDL_Play_vi_Thread, &QThread::finished, SDL_Play_vi, &QObject::deleteLater);
	connect(SDL_Play_vi_Thread, &QThread::finished, SDL_Play_vi_Thread, &QThread::deleteLater);
	SDL_Play_vi_Thread->start();



	vi_Record_Thread = new QThread();
	vi_Record = new RTSPRecord("vi", vi_url);
	vi_Record->moveToThread(vi_Record_Thread);
	connect(this, &fzqjMain_user::Sig_VI_Record_Start, vi_Record, &RTSPRecord::Start);
	connect(Vi_H24Decoder, &RTSPDataDecode::Sig_PacketVi, this, &fzqjMain_user::vi_video_stream_update);
	vi_Record_Thread->start();
	connect(Vi_H24Decoder, &RTSPDataDecode::SigImageChangedVi, this, &fzqjMain_user::vi_img_changed, Qt::DirectConnection);
}

void fzqjMain_user::showIR(void)
{
	QString ir_url = m_Ir_rtsp_path;
	IR_H24Decoder_Thread = new QThread();
	IR_H24Decoder = new RTSPDataDecode("ir", ir_url);
	IR_H24Decoder->moveToThread(IR_H24Decoder_Thread);
	connect(IR_H24Decoder_Thread, &QThread::started, IR_H24Decoder, &RTSPDataDecode::start);
	connect(IR_H24Decoder_Thread, &QThread::finished, IR_H24Decoder, &RTSPDataDecode::stop);
	IR_H24Decoder_Thread->start();

	SDL_Play_ir_Thread = new QThread();
	SDL_Play_ir = new SDL_Play(ir_width, ir_height, "ir", (void*)ui.label_videodisplay_ir->winId());
	SDL_Play_ir->moveToThread(SDL_Play_ir_Thread);
	connect(SDL_Play_ir_Thread, &QThread::started, SDL_Play_ir, &SDL_Play::start);
	connect(SDL_Play_ir_Thread, &QThread::finished, SDL_Play_ir, &SDL_Play::stop);
	SDL_Play_ir_Thread->start();

	Ir_Record_Thread = new QThread();
	Ir_Record = new RTSPRecord("ir", ir_url);
	Ir_Record->moveToThread(Ir_Record_Thread);
	connect(this, &fzqjMain_user::Sig_Ir_Record_Start, Ir_Record, &RTSPRecord::Start);
	connect(IR_H24Decoder, &RTSPDataDecode::Sig_PacketIr, this, &fzqjMain_user::ir_video_stream_update);
	//connect(Ir_Record_Thread, &QThread::finished, Ir_Record, &H264Record::Stop);
	Ir_Record_Thread->start();
	//connect(IR_H24Decoder, &H264DataDecode::SigImageChangedIr, this, &fzqjMain_user::ir_img_changed);
	connect(IR_H24Decoder, &RTSPDataDecode::SigImageChangedIr, this, &fzqjMain_user::ir_img_changed, Qt::DirectConnection);
}

void fzqjMain_user::vi_video_stream_update(AVFormatContext* in_FrameContext, AVPacket* in_pkt)
{
	vi_Record->Update_VideoStream(in_FrameContext, in_pkt);
}

void fzqjMain_user::vi_img_changed(cv::Mat in_mat)
{
	vi_mat = in_mat;
	
}

void fzqjMain_user::ir_video_stream_update(AVFormatContext* in_FrameContext, AVPacket* in_pkt)
{
	Ir_Record->Update_VideoStream(in_FrameContext, in_pkt);
}

void fzqjMain_user::ir_img_changed(cv::Mat in_mat)
{
	ir_mat = in_mat;
	

}

void fzqjMain_user::UpdateRealTimeState(void)
{
	//ui.label_videodisplay_vl->SetTarget((double)(m_pic_up_realtime_state.dsp1_target_x) / 1920.0, (double)(m_pic_up_realtime_state.dsp1_target_y) / 1080.0);
	//ui.label_videodisplay_ir->SetTarget((double)(m_pic_up_realtime_state.dsp2_target_x) / 640.0, (double)(m_pic_up_realtime_state.dsp2_target_y) / 512.0);

	//伺服状态
	QString sfstr = "N/A";
	switch ((int)m_pic_up_realtime_state.mode)
	{
	case 1:
		sfstr = QStringLiteral("扇扫");
		break;
	case 2:
		sfstr = QStringLiteral("周扫");
		break;
	case 4:
		sfstr = QStringLiteral("随动");
		break;
	case 8:
		sfstr = QStringLiteral("跟踪");
		break;
	case 16:
		sfstr = QStringLiteral("收藏");
		break;
	case 32:
		sfstr = QStringLiteral("归零");
		break;
	case 64:
		sfstr = QStringLiteral("伺服停止");
		break;
	case 128:
		sfstr = QStringLiteral("半自动");
		break;
	default:
		break;
	}
	ui.lb_sf_state_2->setText(sfstr);
	ui.lb_sf_fw_2->setText(QString::number(((float)m_pic_up_realtime_state.fw) / 1000, 'f', 3));
	ui.lb_sf_fy_2->setText(QString::number(((float)m_pic_up_realtime_state.fy) / 1000, 'f', 3));
	//视场角
	QString vi_x = QString::number((float)m_pic_up_realtime_state.VIshichang_X / 100, 'f', 2);
	QString vi_y = QString::number((float)m_pic_up_realtime_state.VIshichang_Y / 100, 'f', 2);
	ui.lb_vl_shichang_2->setText(vi_x + "*" + vi_y);
	QString ir_x = QString::number((float)m_pic_up_realtime_state.IRshichang_X / 100, 'f', 2);
	QString ir_y = QString::number((float)m_pic_up_realtime_state.IRshichang_Y / 100, 'f', 2);
	ui.lb_ir_shichang_2->setText(ir_x + "*" + ir_y);
	ui.lb_trackstate_dsp1_2->setText(m_pic_up_realtime_state.dsp1_mode ? QStringLiteral("跟踪") : QStringLiteral("检测"));
	ui.lb_trackstate_dsp2_2->setText(m_pic_up_realtime_state.dsp2_mode ? QStringLiteral("跟踪") : QStringLiteral("检测"));
	//可见光
	double t_dis = m_pic_up_realtime_state.fake_distance;
	//目标经纬高
	m_mycordTrans->targetPolar2TargetGps(weidu, jingdu, gaodu, 0, 0, 0, t_dis, m_pic_up_realtime_state.fw / 1000.0, m_pic_up_realtime_state.fy / 1000.0, t_lat_vl, t_log_vl, t_high_vl);
	//红外
	m_mycordTrans->targetPolar2TargetGps(weidu, jingdu, gaodu, 0, 0, 0, t_dis, m_pic_up_realtime_state.fw / 1000.0, m_pic_up_realtime_state.fy / 1000.0, t_lat_ir, t_log_ir, t_high_ir);
	if (m_pic_up_realtime_state.dsp1_mode)
	{
		ui.lb_target_high->setText(QString::number(t_high_vl, 'f', 3));
	}
	else if (m_pic_up_realtime_state.dsp2_mode)
	{
		ui.lb_target_high->setText(QString::number(t_high_ir, 'f', 3));
	}
	//AI
	QString str_type;
	int temp_Type;
	if (target_manul_type == 0)//AI识别目标类型
	{
		if (m_pic_up_realtime_state.AI_target_type_IR != 0)//同时识别时以红外为准
		{
			temp_Type = m_pic_up_realtime_state.AI_target_type_IR;
		}
		else
		{
			temp_Type = m_pic_up_realtime_state.AI_target_type_VL;
		}
		switch (temp_Type)
		{
		case 0:
			temp_Type = FK_TARGET_UNKNOWN;
			break;
		case 1:
			temp_Type = FK_TARGET_XUANYI_WRJ;
			break;
		case 2:
			temp_Type = FK_TARGET_GUDINGYI_WRJ;
			break;
		case 3:
			temp_Type = FK_TARGET_ZHISHENG;
			break;
		case 4:
			temp_Type = FK_TARGET_KONGPIAOWU;
			break;
		case 5:
			temp_Type = FK_TARGET_KONGPIAOWU;
			break;
		case 6:
			temp_Type = FK_TARGET_MINHANG;
			break;
		default:
			break;
		}
	}
	else//手动设置目标类型
	{
		temp_Type = target_manul_type - 1;
		switch (temp_Type)
		{
		case 0:
			str_type = QStringLiteral("不明");
			break;
		case 1:
			str_type = QStringLiteral("直升机");
			break;
		case 2:
			str_type = QStringLiteral("固定翼无人机");
			break;
		case 3:
			str_type = QStringLiteral("旋翼无人机");
			break;
		case 4:
			str_type = QStringLiteral("民航");
			break;
		case 5:
			str_type = QStringLiteral("车");
			break;
		case 6:
			str_type = QStringLiteral("鸟");
			break;
		case 7:
			str_type = QStringLiteral("空飘球");
			break;
		case 8:
			str_type = QStringLiteral("大型无人机");
			break;
		case 9:
			str_type = QStringLiteral("空飘物");
			break;
		default:
			break;
		}
	}
	//测距
	if (m_pic_up_realtime_state.error_distance == 0xff)
	{
		ui.txt_target_dis->setText(QString::number(m_pic_up_realtime_state.fake_distance));
	}
	else
	{
		QString errorStr;
		switch (m_pic_up_realtime_state.error_distance)
		{
		case 0xDF:
			errorStr = QStringLiteral("无回波");
			break;
		case 0xEF:
			errorStr = QStringLiteral("无主波");
			break;
		case 0xF7:
			errorStr = QStringLiteral("NC");
			break;
		case 0xFB:
			errorStr = QStringLiteral("激光电源故障");
			break;
		case 0xFD:
			errorStr = QStringLiteral("APD电压故障");
			break;
		case 0xFE:
			errorStr = QStringLiteral("信号处理电路故障");
			break;
		default:
			break;
		}
		ui.txt_target_dis->setText(errorStr);
	}
	//发送焦距
	emit sig_focal_length_send(m_pic_up_realtime_state.VIfocuesValue/100, m_pic_up_realtime_state.IRfocuesValue/100);
}

void fzqjMain_user::UpdateSelfCheckState(void)
{
	//状态灯-待更新
	ui.label_vi->setStates(m_pic_up_selfcheck_state.ccdState ? QSimpleLed::ON : QSimpleLed::OFF);
	ui.label_vi->mColor = m_pic_up_selfcheck_state.ccdState ? QSimpleLed::GREEN : QSimpleLed::GREY;
	ui.label_ir->setStates(m_pic_up_selfcheck_state.irState ? QSimpleLed::ON : QSimpleLed::OFF);
	ui.label_ir->mColor = m_pic_up_selfcheck_state.irState ? QSimpleLed::GREEN : QSimpleLed::GREY;
	ui.label_sf->setStates(m_pic_up_selfcheck_state.sfState ? QSimpleLed::ON : QSimpleLed::OFF);
	ui.label_sf->mColor = m_pic_up_selfcheck_state.sfState ? QSimpleLed::GREEN : QSimpleLed::GREY;
	ui.label_cj->setStates(m_pic_up_selfcheck_state.distanceState ? QSimpleLed::ON : QSimpleLed::OFF);
	ui.label_cj->mColor = m_pic_up_selfcheck_state.distanceState ? QSimpleLed::GREEN : QSimpleLed::GREY;
	if (m_bLaserDisStart)
	{
		if (dis_start_index < 10)
		{
			dis_start_index++;
			ui.label_cj->mColor = QSimpleLed::GREY;
		}
		else if (10 < dis_start_index < 30)
		{
			ui.label_cj->mColor = QSimpleLed::GREEN;
			dis_start_index++;
		}
		else
		{
			dis_start_index = 0;
		}
	}
	else
	{
		//
	}
}

void fzqjMain_user::UpdateFKDevState(void)
{
	m_xk_up_devState.devstate = 0;//
	
	m_xk_up_devState.TS = QDateTime::currentDateTime().toMSecsSinceEpoch();
	m_xk_up_devState.ztAz = (m_pic_up_realtime_state.fw / 100) - biaojiaoleida_fw * 10;
	m_xk_up_devState.ztPc = (m_pic_up_realtime_state.fy / 100) - biaojiaoleida_fy * 10;
	if (is_main_camera == 0)
	{
		m_xk_up_devState.view_Zoom = m_pic_up_realtime_state.VIfocuesValue*10;
		m_xk_up_devState.current_camera = 0;
		
	}
	else if (is_main_camera == 1)
	{
		m_xk_up_devState.view_Zoom = m_pic_up_realtime_state.IRfocuesValue * 10;
		m_xk_up_devState.current_camera = 1;
		
	}
	
	m_xk_up_devState.Lon = jingdu * 1000000;
	m_xk_up_devState.Lat = weidu * 1000000;
	m_xk_up_devState.Alt = gaodu * 100;
	int trackState = 0;//未跟踪
	int pix_nums = 0;
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)//跟踪
	{
		
		trackState = 1;
		if (m_pic_up_realtime_state.dsp1_mode)
		{
			pix_nums = m_pic_up_realtime_state.ai_vi_size;
		}
		if (m_pic_up_realtime_state.dsp2_mode)
		{
			pix_nums = m_pic_up_realtime_state.ai_ir_size;
		}
	}
	else if (m_pic_up_realtime_state.mode == 1 || m_pic_up_realtime_state.mode == 2)//搜索 扇扫/周扫
	{
		trackState = 0;
	}
	
	m_xk_up_devState.pixel_nums = pix_nums;
	m_xk_up_devState.trackState = trackState;//trackState
	if (m_pic_up_realtime_state.dsp1_mode == 1)
	{
		m_xk_up_devState.targetAz = (m_pic_up_realtime_state.dsp1_target_fw + m_pic_up_realtime_state.fw) / 100;
		m_xk_up_devState.targetAz -= biaojiaoleida_fw * 10;
		m_xk_up_devState.targetPc = (m_pic_up_realtime_state.dsp1_target_fy + m_pic_up_realtime_state.fy) / 100;
		m_xk_up_devState.targetPc -= biaojiaoleida_fy * 10;
	}
	else if (m_pic_up_realtime_state.dsp2_mode == 1)
	{
		m_xk_up_devState.targetAz = (m_pic_up_realtime_state.dsp2_target_fw + m_pic_up_realtime_state.fw) / 100;
		m_xk_up_devState.targetAz -= biaojiaoleida_fw * 10;
		m_xk_up_devState.targetPc = (m_pic_up_realtime_state.dsp2_target_fy + m_pic_up_realtime_state.fy) / 100;
		m_xk_up_devState.targetPc -= biaojiaoleida_fy * 10;
	}
	else
	{
		m_xk_up_devState.targetAz = 0;
		m_xk_up_devState.targetPc = 0;
	}
	m_xk_up_devState.targetDis = m_pic_up_realtime_state.fake_distance;
	if (target_manul_type != 0)
	{
		m_xk_up_devState.targetType = target_manul_type - 1;//0为自动，手动选择从1开始
	}
	else
	{
		int temp_Type = m_pic_up_realtime_state.AI_target_type_VL ? m_pic_up_realtime_state.AI_target_type_VL : m_pic_up_realtime_state.AI_target_type_IR;
		switch (temp_Type)
		{
		case 0:
			m_xk_up_devState.targetType =(uint8_t)FK_TARGET_UNKNOWN;
			break;
		case 1:
			m_xk_up_devState.targetType = (uint8_t)FK_TARGET_XUANYI_WRJ;
			break;
		case 2:
			m_xk_up_devState.targetType = (uint8_t)FK_TARGET_GUDINGYI_WRJ;
			break;
		case 3:
			m_xk_up_devState.targetType = (uint8_t)FK_TARGET_ZHISHENG;
			break;
		case 4:
			m_xk_up_devState.targetType = (uint8_t)FK_TARGET_KONGPIAOWU;
			break;
		case 5:
			m_xk_up_devState.targetType = (uint8_t)FK_TARGET_KONGPIAOWU;
			break;
		case 6:
			m_xk_up_devState.targetType = (uint8_t)FK_TARGET_MINHANG;
			break;
		default:
			break;
		}
	}
	ui.txt_target_dis->setText(QString::number(m_xk_up_devState.targetDis));
	//原为0，防控说100000好进行判断,进入跟踪状态若未能对物体进行测距成功,则发送100000
	if (m_xk_up_devState.trackState == 1)
	{
		if (m_xk_up_devState.targetDis == 0)
		{
			m_xk_up_devState.targetDis = 100000;
		}
		else if (m_xk_up_devState.targetDis > 10000)
		{
			m_xk_up_devState.targetDis = 100000;
		}
	}
	//m_xk_up_devState.pixel_nums = 1000;
	//m_xk_up_devState.targetDis = 2000;
}

void fzqjMain_user::InitConfigInfo(void)
{
	m_Video_ip = m_xk_configinfo.XK_IP;
	m_PicIP = m_xk_configinfo.GD_IP;
	m_Vi_rtsp_path = m_xk_configinfo.VI_RTSP_Addr;
	m_Ir_rtsp_path = m_xk_configinfo.IR_RTSP_Addr;
	m_VI_port = m_xk_configinfo.VI_H264_Port;//13010
	m_IR_port = m_xk_configinfo.IR_H264_Port;//13000
	m_sendPic_port = m_xk_configinfo.XK_Send_GD_INFO_Port;
	m_recvPic_port = m_xk_configinfo.XK_Recv_GD_INFO_Port;
	m_recvPic_SelfCheck_port = m_xk_configinfo.XK_Recv_GD_INFO_Port;
	m_FK_ip = m_xk_configinfo.FK_IP;
	m_send_FK_heart_port = m_xk_configinfo.XK_Send_FK_INFO_Port;//35498
	m_send_FK_devState_port = m_xk_configinfo.XK_Send_FK_INFO_Port;
	m_send_FK_target_port = m_xk_configinfo.XK_Send_FK_INFO_Port;
	m_Recv_FK_yindao_port = m_xk_configinfo.FK_Send_XK_INFO_Port;
	isSoundPlay4Warning = m_xk_configinfo.IS_WARNING_TARGET;
	jingdu = m_xk_configinfo.this_jingdu;
	weidu = m_xk_configinfo.this_weidu;
	gaodu = m_xk_configinfo.this_gaodu;
	ui.txt_jingdu->setText(QString::number(jingdu, 'f', 6));
	ui.txt_weidu->setText(QString::number(weidu, 'f', 6));
	ui.txt_gaodu->setText(QString::number(gaodu, 'f', 6));
	m_xk_up_heart.devID[0] = (m_xk_configinfo.devID >> 24) & 0xff;
	m_xk_up_heart.devID[1] = (m_xk_configinfo.devID >> 16) & 0xff;
	m_xk_up_heart.devID[2] = (m_xk_configinfo.devID >> 8) & 0xff;
	m_xk_up_heart.devID[3] = m_xk_configinfo.devID & 0xff;
	m_xk_up_heart.sourceID = m_xk_configinfo.sourceID;
	m_xk_up_devState.devID[0] = (m_xk_configinfo.devID >> 24) & 0xff;
	m_xk_up_devState.devID[1] = (m_xk_configinfo.devID >> 16) & 0xff;
	m_xk_up_devState.devID[2] = (m_xk_configinfo.devID >> 8) & 0xff;
	m_xk_up_devState.devID[3] = m_xk_configinfo.devID & 0xff;
	m_xk_up_devState.sourceID = m_xk_configinfo.sourceID;
	m_xk_up_log.devID[0] = (m_xk_configinfo.devID >> 24) & 0xff;
	m_xk_up_log.devID[1] = (m_xk_configinfo.devID >> 16) & 0xff;
	m_xk_up_log.devID[2] = (m_xk_configinfo.devID >> 8) & 0xff;
	m_xk_up_log.devID[3] = m_xk_configinfo.devID & 0xff;
	m_xk_up_log.sourceID = m_xk_configinfo.sourceID;
}

void fzqjMain_user::InitConfigBtn(void)
{
	if (m_xk_configinfo.IS_GUIDE_ADAPT_VIEW == 1)
	{
		ui.btn_Lidar_YinDao_Focus->setText(QStringLiteral("自动变焦中..."));
		SetBtnHighLight(ui.btn_Lidar_YinDao_Focus, true);
		is_guideing = true;
		m_timer500->start();
	}
	else if (m_xk_configinfo.IS_GUIDE_ADAPT_VIEW == 0)
	{
		ui.btn_Lidar_YinDao_Focus->setText(QStringLiteral("引导自动变焦"));
		SetBtnHighLight(ui.btn_Lidar_YinDao_Focus, false);
		is_guideing = false;

	}
}

void fzqjMain_user::sendMsg2Pic(XKDownMsg xk_down_msg)
{
	QByteArray buffer;
	buffer.resize(sizeof(XKDownMsg));
	memcpy(buffer.data(), &xk_down_msg, sizeof(XKDownMsg));
	m_socket->SendDatagram(buffer, QHostAddress(m_PicIP), m_sendPic_port);
}

void fzqjMain_user::RefreshGDConfig(void)
{
	//
}

void fzqjMain_user::InitSFyzw(void)
{
	ui.cbx_sf_yzw_num->clear();
	for (int i = 1; i < 51; i++)
	{
		QString key = "SF_";
		key.append(QString::number(i));
		std::string value = m_configManager->read(key.toStdString(), "");
		m_sf_yzw_list.append(QString::fromStdString(value));
		ui.cbx_sf_yzw_num->addItem(QString::fromStdString(value));
	}
}
void fzqjMain_user::on_btn_SetDevLocation_clicked(void)
{
	//打开经纬高设置界面
	jingdu = ui.txt_jingdu->text().toDouble();
	weidu = ui.txt_weidu->text().toDouble();
	gaodu = ui.txt_gaodu->text().toDouble();
	//判断是否正确数值
	vector<double> errorDataList;
	if (jingdu < 0 || jingdu > 180)
	{
		errorDataList.push_back(jingdu);
	}
	if (weidu < 0 || weidu > 90)
	{
		errorDataList.push_back(weidu);
	}
	if (errorDataList.size() > 0)
	{
		for (int i = 0; i < errorDataList.size(); i++)
		{
			QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("非法的数值: \"%1\"").arg(errorDataList[i]));
		}
		return;
	}
	m_xk_up_devState.Lon = jingdu * 1000000;
	m_xk_up_devState.Lat = weidu * 1000000;
	m_xk_up_devState.Alt = gaodu * 100;

	m_configManager->set("this_jingdu", ui.txt_jingdu->text().toStdString());
	m_configManager->set("this_weidu", ui.txt_weidu->text().toStdString());
	m_configManager->set("this_gaodu", ui.txt_gaodu->text().toStdString());
	m_configManager->print("Config.ini");
	QString str = QStringLiteral("激光测距-设备位置-设置");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_CountSize_clicked(void)
{
	bool Is_Windows_Open = is_windows_open("fzqjGetPicSize");
	QString str = QStringLiteral("计算面积-更多设置-打开");
	ShowLineText(0, 0, str);
	if (Is_Windows_Open == false)
	{
		return;
	}
	else
	{
		fzqjGetPicSize* w = new fzqjGetPicSize();
		w->setAttribute(Qt::WA_DeleteOnClose, true);
		connect(this, &fzqjMain_user::Sig_Img_Circle, w, &fzqjGetPicSize::updateImageMat);
		connect(this, &fzqjMain_user::sig_focal_length_send, w, &fzqjGetPicSize::updateFocalLength);
		w->show();
	}
}

void fzqjMain_user::SetBtnHighLight(QWidget* btn, bool flag)
{
	if (flag)//0E7788 F0FFFF
	{
		btn->setStyleSheet("background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,stop : 0 #F0FFFF, stop: 0.5 #09121A,stop: 1.0 #F0FFFF);    border - color: #11505C; ");
	}
	else
	{
		btn->setStyleSheet("");
	}
}

void fzqjMain_user::SetMainCamera(bool flag)
{
	if (!flag)//可见光
	{
		b_yaogan_mainCamera = false;
		m_xk_down_msg.msg_type = E_FK_SWITCH_VL;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
	}
	else
	{
		b_yaogan_mainCamera = true;
		m_xk_down_msg.msg_type = E_FK_SWITCH_IR;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
	}
}

void fzqjMain_user::SetDevDateTime(void)
{
	time_t timeReal;
	time(&timeReal);
	timeReal = timeReal + 8 * 3600;
	tm* nowTime = gmtime(&timeReal);
	m_xk_down_msg.msg_type = E_FK_SET_TIME;
	m_xk_down_msg.param_1 = (nowTime->tm_year + 1900) * 10000 + (nowTime->tm_mon + 1) * 100 + nowTime->tm_mday;
	m_xk_down_msg.param_2 = nowTime->tm_hour;
	m_xk_down_msg.param_3 = nowTime->tm_min;
	m_xk_down_msg.param_4 = nowTime->tm_sec;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

int fzqjMain_user::t_SF_Stop(void)
{
	Sleep(100);
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = 0;
	m_xk_down_msg.param_2 = 0;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_SF_STOP;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	return 0;
}
/**
 * @brief 判断当前方位俯仰是否在禁止区域内
 * @param current_azimuth 当前方位角（0-360度）
 * @param current_elevation 当前俯仰角
 * @param az_start 禁止区域方位起始角
 * @param az_end 禁止区域方位终止角
 * @param el_start 禁止区域俯仰起始角
 * @param el_end 禁止区域俯仰终止角
 * @return true 在禁止区域内，false 不在禁止区域内
 */
bool fzqjMain_user::isInNoZone(float current_azimuth, float current_elevation, float az_start, float az_end, float el_start, float el_end)
{
	// 检查俯仰角是否在范围内
	bool in_elevation = (current_elevation >= el_start) && (current_elevation <= el_end);

	// 检查方位角是否在范围内
	bool in_azimuth;
	if (az_start <= az_end) {
		// 正常情况（不跨越0°）
		in_azimuth = (current_azimuth >= az_start) && (current_azimuth <= az_end);
	}
	else {
		// 跨越0°的情况（如 340°~20°）
		in_azimuth = (current_azimuth >= az_start) || (current_azimuth <= az_end);
	}

	// 同时满足方位和俯仰条件才返回 true
	return in_azimuth && in_elevation;
}
HEALTH_CTL_MSG fzqjMain_user::getWatchDogMsg(int state)
{
	HEALTH_CTL_MSG message;
	memset((char*)&message, 0, sizeof(HEALTH_CTL_MSG));
	switch (state)
	{
	case 0:
	{
		message.AReboot = 1;
		break;
	}
	case 1:
	{
		message.AutoReboot = 1;
		break;
	}
	case 2:
	{
		message.AutoReboot = 2;
		break;
	}
	case 3:
	{
		message.AKill = 1;
		break;
	}
	default:
		break;
	}
	return message;
}
static double last_zkyd_fw = 0;
void fzqjMain_user::OnRecvFKData(QByteArray data)
{
	//ShowLineText(1, "指控", data.toHex().toUpper());
	uint16_t command = (data[54] << 8) & 0xff00 | (data[53] & 0xff);
	FKDownMessageTypeEnum a;
	int guide = 0;
	switch (command)
	{
	case FKDOWN_TARGET_GUIDE:
	{
		if (isGetLeiDaYinDao)
		{
			guide = 1;
			guide_index = 0;
			memcpy(&m_fk_down_guide, data, sizeof(FKDownGuideMsg));
			//目标经纬高转方位俯仰
			double t_jingdu = (double)m_fk_down_guide.Lon / 1000000.0;
			double t_weidu = (double)m_fk_down_guide.Lat / 1000000.0;
			double t_gaodu = (double)m_fk_down_guide.Alt / 100.0;
			is_yindao_send = true;

			double t_fw, t_fy, t_dis;
			t_dis = 0;
			m_mycordTrans->targetGps2TargetPolar(weidu, jingdu, gaodu, t_weidu, t_jingdu, t_gaodu, 0, 0, 0, t_dis, t_fw, t_fy);
			ShowLineText(1, QStringLiteral("指控"), QStringLiteral("FKDOWN_TARGET_GUIDE：目标经度：%1，目标纬度：%2，目标高度：%3，目标距离：%4,引导方位：%5，引导俯仰：%6").arg(t_jingdu, 10, 'f', 6, 0).arg(t_weidu, 10, 'f', 6, 0).arg(t_gaodu, 10, 'f', 6, 0).arg(t_dis, 10, 'f', 6, 0).arg(t_fw, 10, 'f', 3, 0).arg(t_fy, 10, 'f', 3, 0));
			gudie_dis = t_dis;
			yindao_fw = t_fw*1000;
			yindao_fy = t_fy*1000;
			m_logRealTime->writeLog
			(
				QStringLiteral("this_lat,%1,this_lot,%2,this_h,%3,t_lat,%4,t_lot,%5,t_h,%6,t_fw,%7,t_fy,%8,t_dis,%9")
				.arg(weidu, 10, 'f', 6, 0)
				.arg(jingdu, 10, 'f', 6, 0)
				.arg(gaodu, 10, 'f', 6, 0)
				.arg(t_weidu, 10, 'f', 6, 0)
				.arg(t_jingdu, 10, 'f', 6, 0)
				.arg(t_gaodu, 10, 'f', 6, 0)
				.arg(t_fw, 10, 'f', 6, 0)
				.arg(t_fy, 10, 'f', 6, 0)
				.arg(t_dis, 10, 'f', 6, 0)
				.toStdString()
			);
			t_fw += biaojiaoleida_fw;
			t_fy += biaojiaoleida_fy;
			if (t_fw < 0)
			{
				t_fw += 360;
			}
			//转台控制
			if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
			{
				qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
				return;
			}
			int x =(int)(t_fw * 1000);
			int y = (int)(t_fy * 1000);
			m_xk_down_msg.msg_type = E_FK_SF_MOVE_TO;
			m_xk_down_msg.param_1 = x;
			m_xk_down_msg.param_2 = y;
			sendMsg2Pic();
			m_xk_down_msg.msg_type = E_FK_BUTT;
		}
		break;
	}
	case FKDOWN_POWER_CONTROL:
		ShowLineText(1, QStringLiteral("指控"), "FKDOWN_POWER_CONTROL");
		memcpy(&m_fk_down_powerControl, data, sizeof(FKDownPowerControlMsg));
		if (!m_fk_down_powerControl.ztPower)//暂时无上下电，都是刹车
		{
			on_btn_sf_stop_clicked();
		}
		else
		{
			on_btnMid_pressed();
		}
		if (!m_fk_down_powerControl.vlPower)//可见光上下电
		{
			on_toolButton_VI_ON_clicked();
		}
		else
		{
			on_toolButton_VI_OFF_clicked();
		}
		if (!m_fk_down_powerControl.irPower)//红外上下电
		{
			on_toolButton_IR_ON_clicked();
		}
		else
		{
			on_toolButton_IR_OFF_clicked();
		}
		if (!m_fk_down_powerControl.lanserPower)//测距机上下电
		{
			on_toolButton_laser_ON_clicked();
		}
		else
		{
			on_toolButton_laser_OFF_clicked();
		}
		break;
	case FKDOWN_ZT_CONTROL:
		ShowLineText(1, QStringLiteral("指控"), "FKDOWN_ZT_CONTROL");
		memcpy(&m_fk_down_ztCntrol, data, sizeof(FKDownZTControlMsg));
		if (m_fk_down_ztCntrol.CentrlContrl == 0)//开始控制
		{
			if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
			{
				qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
				return;
			}
			else
			{
				switch (m_fk_down_ztCntrol.ContrlTurnl)
				{
				case 0://停止运动
					sendSFshache();
					break;
				case 1://向左运动
					on_btnLeft_pressed();//左
					break;
				case 2://向右运动
					on_btnRight_pressed();//右
					break;
				case 3://向上运动
					on_btnTop_pressed();//上
					break;
				case 4://向下运动
					on_btnBottom_pressed();//下
					break;
				default:
					break;
				}
			}
		}
		break;
	case FKDOWN_VL_CONTROL:
		ShowLineText(1, QStringLiteral("指控"), "FKDOWN_VL_CONTROL");
		memcpy(&m_fk_down_vlCntrol, data, sizeof(FKDownVLControlMsg));
		if (m_fk_down_vlCntrol.CentrlContrl == 0)//开始控制
		{
			switch (m_fk_down_vlCntrol.ContrlTurnl)
			{
			case 0://停止运动
				vl_zk_stop();
				break;
			case 1://长焦
				on_btn_vl_v_add_pressed();//变倍+
				break;
			case 2://短焦
				on_btn_vl_v_nadd_pressed();;//变倍-
				break;
			case 3://聚焦
				on_btn_vl_focue_add_pressed();//调焦+
				break;
			case 4://聚焦
				on_btn_vl_focuse_minus_pressed();//调焦-
				break;
			case 5://透雾关
				btn_vl_qw_open(0);//透雾关
				break;
			case 6://透雾开
				btn_vl_qw_open(5);//透雾开
				break;
			case 7://自动聚焦
				on_btn_vl_auto_focuse_clicked();//自动调焦
				break;
			default:
				break;
			}
		}
		break;
	case FKDOWN_IR_CONTROL:
		ShowLineText(1, QStringLiteral("指控"), "FKDOWN_IR_CONTROL");
		memcpy(&m_fk_down_irCntrol, data, sizeof(FKDownIRControlMsg));
		if (m_fk_down_irCntrol.CentrlContrl == 0)//开始控制
		{
			switch (m_fk_down_irCntrol.ContrlTurnl)
			{
			case 0://停止运动
				ir_zk_stop();
				break;
			case 1://长焦
				on_btn_ir_v_add_pressed();//变倍+
				break;
			case 2://短焦
				on_btn_ir_v_nadd_pressed();//变倍-
				break;
			case 3://聚焦
				on_btn_ir_focue_add_pressed();//调焦+
				break;
			case 4://聚焦
				on_btn_ir_focuse_minus_pressed();//调焦-
				break;
			case 5://校正
				ir_manul_correction();//红外快门校正
				break;
			case 6://
				break;
			case 7://自动聚焦
				on_btn_ir_auto_focuse_clicked();//自动调焦
				break;
			default:
				break;
			}
		}
		break;
	case FKDOWN_GD_PROTECT:
		ShowLineText(1, "指控", "FKDOWN_GD_PROTECT");
		memcpy(&m_fk_down_gdProtect, data, sizeof(FKDownGDprotectMsg));
		//下发开关指令给下位机        
		sendMsg2Pic();
		if (!m_fk_down_gdProtect.secure)
		{
			m_xk_down_msg.msg_type = E_FK_OPEN_GD_PROTECT;
		}
		else
		{
			m_xk_down_msg.msg_type = E_FK_CLOSE_GD_PROTECT;
		}
		break;
	case FKUP_MAX_STATE_E:
		break;
	default:
		break;
	}
	if (guide == 0)
	{
		guide_index++;
	}
	if (guide_index>3)
	{
		is_yindao_send = false;
		gudie_dis = 0;
	}
}

void fzqjMain_user::OnTimeOut30000(void)
{
	on_btn_selfCheck_clicked();
}

void fzqjMain_user::OnTimeOut1000(void)
{
	//连续激光测距
	if (m_bLaserDisStart)
	{
		float current_fw = m_pic_up_realtime_state.fw / 1000;
		float current_fy = m_pic_up_realtime_state.fy / 1000;
		bool ret = isInNoZone(current_fw, current_fy, m_xk_configinfo.laser_forbid_fw_start,
			m_xk_configinfo.laser_forbid_fw_stop, m_xk_configinfo.laser_forbid_fy_start, m_xk_configinfo.laser_forbid_fy_stop);
		if (!ret)
		{
			on_btn_start_1_dis_2_clicked();
		}
		
		av_usleep(10);
	}
	if (b_pingPic == true)
	{
		//上报心跳
		sendHeartMsg2FK();
		//上报设备状态
		sendDevStateMsg2FK();
	}
	if (m_pic_up_realtime_state.fake_distance > 0 && m_pic_up_realtime_state.fake_distance < 10000)
	{
		QString str = QStringLiteral("激光测距距离：%1").arg(QString::number((double)m_pic_up_realtime_state.fake_distance, 'f', 3));
		ShowLineText(0, 0, str);
	}
	emit Sig_Img_Circle(vi_mat, ir_mat);
	QDateTime currentTime = QDateTime::currentDateTime();
	QString timeStr = currentTime.toString("yyyy-MM-dd hh:mm:ss");
	ui.lb_currectTime->setText(timeStr);
	//qDebug() << "vizoom: % d" << m_pic_up_realtime_state.VIzoomValue;
}

void fzqjMain_user::OnTimeOut500(void)
{

	guideAutoFocus();
	/*cout << m_pic_up_realtime_state.IRfocuesValue<<"\n";*/

}

void fzqjMain_user::OnTimeOut100(void)
{
	if (m_xk_down_msg.msg_type == E_FK_SF_MOVE)
	{
		if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
		{
			qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
			return;
		}
		sendMsg2Pic();
	}
	if (m_xk_down_msg.msg_type == E_FK_SF_STOP)
	{
		sendMsg2Pic();
		//if (ui.lb_sf_state->text() == QStringLiteral("伺服停止"))
		if ((int)m_pic_up_realtime_state.mode == 64)
		{
			m_timer20->stop();
			m_xk_down_msg.msg_type == E_FK_BUTT;
		}
	}
}

void fzqjMain_user::sendReportMsg(XKUpDevStateMsg in_msg)
{
	QString str = QStringLiteral("手动上报-上发");
	ShowLineText(0, 0, str);
	QByteArray buffer;
	buffer.resize(sizeof(XKUpDevStateMsg));
	memcpy(buffer.data(), &in_msg, sizeof(XKUpDevStateMsg));
	m_socket->SendDatagram(buffer, QHostAddress(m_FK_ip), m_send_FK_heart_port);
	QString str_type;
	switch (in_msg.targetType)
	{
	case 0:
		str_type = QStringLiteral("不明");
		break;
	case 1:
		str_type = QStringLiteral("直升机");
		break;
	case 2:
		str_type = QStringLiteral("固定翼无人机");
		break;
	case 3:
		str_type = QStringLiteral("旋翼无人机");
		break;
	case 4:
		str_type = QStringLiteral("民航");
		break;
	case 5:
		str_type = QStringLiteral("车");
		break;
	case 6:
		str_type = QStringLiteral("鸟");
		break;
	case 7:
		str_type = QStringLiteral("空飘球");
		break;
	case 8:
		str_type = QStringLiteral("大型无人机");
		break;
	case 9:
		str_type = QStringLiteral("空飘物");
		break;
	default:
		break;
	}
	QString checkStr = QStringLiteral("本机经度:%1,本机纬度:%2,本机高度:%3,目标类型:%4,目标方位:%5,目标俯仰:%6,目标距离:%7")
		.arg(QString::number((double)in_msg.Lon / 1000000.0, 'f', 6))
		.arg(QString::number((double)in_msg.Lat / 1000000.0, 'f', 6))
		.arg(QString::number((double)in_msg.Alt / 100.0, 'f', 2))
		.arg(str_type)
		.arg(QString::number((double)in_msg.ztAz / 10.0))
		.arg(QString::number((double)((int16_t)in_msg.ztPc) / 10.0))
		.arg(in_msg.targetDis);
	ShowLineText(0, QStringLiteral("手动上报"), checkStr);//打印字符串
	qDebug() << "state:" << in_msg.trackState << "size:" << buffer.size();
}

void fzqjMain_user::pingFkRes(bool res)
{
	b_pingFK = res;
	ui.label_SJK->setStates(res ? QSimpleLed::ON : QSimpleLed::OFF);
	ui.label_SJK->mColor = res ? QSimpleLed::GREEN : QSimpleLed::GREY;
}

void fzqjMain_user::pingPicRes(bool res)
{
	if ((!b_pingPic) && (res))//之前掉线，现在连上，下发时间
	{
		SetDevDateTime();
	}
	b_pingPic = res;
	if (!res)
	{
		ui.label_vi->setStates(QSimpleLed::OFF);
		ui.label_ir->setStates(QSimpleLed::OFF);
		ui.label_cj->setStates(QSimpleLed::OFF);
		ui.label_sf->setStates(QSimpleLed::OFF);
		//ui.label_SJK->setStates(QSimpleLed::OFF);
		ui.label_vi->mColor = QSimpleLed::GREY;
		ui.label_ir->mColor = QSimpleLed::GREY;
		ui.label_cj->mColor = QSimpleLed::GREY;
		ui.label_sf->mColor = QSimpleLed::GREY;
		//ui.label_SJK->mColor = QSimpleLed::GREY;
		ui.label_videodisplay_vl->setStyleSheet("background-color: rgb(61, 61, 134);");
		ui.label_videodisplay_ir->setStyleSheet("background-color: rgb(61, 61, 134);");
	}
}


void fzqjMain_user::sendConfig2Pic(XKDownConfig xk_down_config)
{
	QByteArray buffer;
	buffer.resize(sizeof(XKDownConfig));
	memcpy(buffer.data(), &xk_down_config, sizeof(XKDownConfig));
	m_socket->SendDatagram(buffer, QHostAddress(m_PicIP), m_sendPic_port);
}

void fzqjMain_user::InitConfigInfo(XKConfigInfo xk_configinfo)
{
	m_xk_configinfo = xk_configinfo;
	InitConfigInfo();
}

void fzqjMain_user::OnRecvData(QByteArray data)
{
	//ShowLineText(1,0,data.toHex().toUpper());
	int recvLen = data.length();
	if (data[0] == (char)0x55 && data[1] == (char)0xAA)
	{
		switch (data[2])
		{
		case  FKUP_SELFCHECK_STATE_E:
			if (recvLen == sizeof(PICUpSelfCheckStateStruct))
			{
				memcpy(&m_pic_up_selfcheck_state, data, sizeof(PICUpSelfCheckStateStruct));
				//更新自检信息
				UpdateSelfCheckState();
			    //打印自检信息
				if (bPrintSelfCheckTime)
				{
					bPrintSelfCheckTime = false;
					QString checkStr = QStringLiteral("可见光:%1,红外:%2,测距机:%3,伺服:%4,AI检测器:%5,DSP跟踪器:%6,温度1:%7,温度2:%8,湿度:%9,气压:%10")
						.arg(int8C_to_OpenorClose(m_pic_up_selfcheck_state.ccdState))
						.arg(int8C_to_OpenorClose(m_pic_up_selfcheck_state.irState))
						.arg(int8C_to_OpenorClose(m_pic_up_selfcheck_state.distanceState))
						.arg(int8C_to_StateInfo(m_pic_up_selfcheck_state.sfState))
						.arg(int8C_to_OpenorClose(m_pic_up_selfcheck_state.detectorState))
						.arg(int8C_to_OpenorClose(m_pic_up_selfcheck_state.traceState))
						.arg(int8C_to_StateInfo(1))
						.arg(m_pic_up_selfcheck_state.boardtemp1)
						.arg(m_pic_up_selfcheck_state.boardtemp2)
						.arg(m_pic_up_selfcheck_state.boardHumidity)
						.arg(m_pic_up_selfcheck_state.boardPressure);
					ShowLineText(1, QStringLiteral("自检"), checkStr);//打印字符串
					//保存日志
					if (m_bSaveSelfCheckMsg)
					{
						m_logSelfCheck->writeLog
						(
							QStringLiteral("可见光:%1,红外:%2,测距机:%3,伺服:%4,AI检测器:%5,DSP跟踪器:%6,数据库:%7,温度1:%8,温度2:%9,湿度:%10,气压:%11,")
							.arg(int8C_to_OpenorClose(m_pic_up_selfcheck_state.ccdState))
							.arg(int8C_to_OpenorClose(m_pic_up_selfcheck_state.irState))
							.arg(int8C_to_OpenorClose(m_pic_up_selfcheck_state.distanceState))
							.arg(int8C_to_StateInfo(m_pic_up_selfcheck_state.sfState))
							.arg(int8C_to_OpenorClose(m_pic_up_selfcheck_state.detectorState))
							.arg(int8C_to_OpenorClose(m_pic_up_selfcheck_state.traceState))
							.arg(int8C_to_StateInfo(1))
							.arg(m_pic_up_selfcheck_state.boardtemp1)
							.arg(m_pic_up_selfcheck_state.boardtemp2)
							.arg(m_pic_up_selfcheck_state.boardHumidity)
							.arg(m_pic_up_selfcheck_state.boardPressure)
							.toStdString()
						);
					}
				}				
			}
			else
			{
				qDebug() << "recv len" << recvLen << "expect len" << sizeof(PICUpSelfCheckStateStruct);
			}
			break;
		case  FKUP_REALTIME_STATE_E:
			if (recvLen == sizeof(PICUpRealTimeStateMsgStruct))
			{
				//目标是否新增进数据库
				int oldTrackState = false;
				if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
				{
					oldTrackState = true;
				}
				memcpy(&m_pic_up_realtime_state, data, sizeof(PICUpRealTimeStateMsgStruct));
				//伺服北向修正：test
				m_pic_up_realtime_state.fw -= beixiang0shidangqianfangweilinshiyonglaixiuzheng;
				if (m_pic_up_realtime_state.fw < 0)
				{
					m_pic_up_realtime_state.fw += 360000;
				}
				//更新实时状态
				UpdateRealTimeState();
				//更新上报防控状态
				UpdateFKDevState();
				//目标报警
				if (isSoundPlay4Warning)
				{
					if (m_pic_up_realtime_state.AI_target_type_VL != 0 || m_pic_up_realtime_state.AI_target_type_IR != 0)
					{
						
						if (!isQSoundPlaying)
						{
							ui.label_BG->setStates(QSimpleLed::ON);
							ui.label_BG->mColor = QSimpleLed::RED;
							//qDebug() << "red";
							isQSoundPlaying = true;
							//播放报警音乐
							warningSound->play();
							
						}
					}
					else
					{
						//ui.label_BG->mColor = QSimpleLed::GREY;
						if (isQSoundPlaying)
						{
							ui.label_BG->setStates(QSimpleLed::OFF);
							ui.label_BG->mColor = QSimpleLed::GREY;
							//qDebug() << "grey";
							warningSound->stop();
							isQSoundPlaying = false;
						}
					}
				}
				
                //新增记录
                QString str_type1 = QStringLiteral("无");
                QString str_type2 = QStringLiteral("无");
                //if ((!isNewTrackTargetInsert) && (m_pic_up_realtime_state.dsp1_mode))
                {
                    int temp_Type1 = m_pic_up_realtime_state.AI_target_type_VL;//目标类型
                    switch (temp_Type1)
                    {
                    case 0:
                        str_type1 = QStringLiteral("无");
                        break;
                    case 1:
                        str_type1 = QStringLiteral("旋翼无人机");
                        break;
                    case 2:
                        str_type1 = QStringLiteral("固定翼无人机");
                        break;
                    case 3:
                        str_type1 = QStringLiteral("直升机");
                        break;
                    case 4:
                        str_type1 = QStringLiteral("空飘物");//气球
                        break;
                    case 5:
                        str_type1 = QStringLiteral("空飘物");//热气球
                        break;
                    default:
                        break;
                    }
                }
                //else if (!isNewTrackTargetInsert && m_pic_up_realtime_state.dsp2_mode)
                {
                    int temp_Type2 = m_pic_up_realtime_state.AI_target_type_IR;//目标类型
                    switch (temp_Type2)
                    {
                    case 0:
                        str_type2 = QStringLiteral("无");
                        break;
                    case 1:
                        str_type2 = QStringLiteral("旋翼无人机");
                        break;
                    case 2:
                        str_type2 = QStringLiteral("固定翼无人机");
                        break;
                    case 3:
                        str_type2 = QStringLiteral("直升机");
                        break;
                    case 4:
                        str_type2 = QStringLiteral("空飘物");//气球
                        break;
                    case 5:
                        str_type2 = QStringLiteral("空飘物");//热气球
                        break;
                    default:
                        break;
                    }
                }
				
				//日志
				if (m_bSaveRealTimeMsg)
				{
					m_logRealTime->writeLog
					(
						QStringLiteral("可见光视场X,%1,可见光视场Y,%2,红外视场X,%3,红外视场Y,%4,方位,%5,俯仰,%6,模式,%7,可见光目标方位,%8,可见光目标俯仰,%9,红外目标方位,%10,红外目标俯仰,%11,目标距离,%12,发送防控距离，%13,识别物，%14,%15")
						.arg(m_pic_up_realtime_state.VIshichang_X)
						.arg(m_pic_up_realtime_state.VIshichang_Y)
						.arg(m_pic_up_realtime_state.IRshichang_X)
						.arg(m_pic_up_realtime_state.IRshichang_Y)
						.arg(m_pic_up_realtime_state.fw)
						.arg(m_pic_up_realtime_state.fy)
						.arg(ui.lb_sf_state_2->text())
						.arg(m_pic_up_realtime_state.dsp1_target_fw)
						.arg(m_pic_up_realtime_state.dsp1_target_fy)
						.arg(m_pic_up_realtime_state.dsp2_target_fw)
						.arg(m_pic_up_realtime_state.dsp2_target_fy)
						.arg(m_pic_up_realtime_state.fake_distance)
						.arg(m_xk_up_devState.targetDis)
						.arg(str_type1)
						.arg(str_type2)
						.toStdString()
					);
					if (is_send_fk == true)
					{
						m_logRealTime->writeLog(timeStrfk.toStdString());
						is_send_fk = false;
					}
					else
					{
						//
					}

				}
			}
			else
			{
				qDebug() << "recv len" << recvLen << "expect len" << sizeof(PICUpRealTimeStateMsgStruct);
			}
			break;
		case  FKUP_CONFIG_INFO_E:
			memcpy(&m_gd_configinfo, data, sizeof(GDConfigInfo));
			emit sig_RefreshGDConfig(m_gd_configinfo);
			break;
		case FKUP_DWDX_INFO_E:
		{
			memcpy(&m_beidou_info, data, sizeof(RecvBeiDouInfo));
			//打印到窗口
			QString print_Longitude = QString::number(m_beidou_info.Longitude, 'f', 6);
			QString print_Latitude = QString::number(m_beidou_info.Latitude, 'f', 6);
			QString print_Altitude = QString::number(m_beidou_info.Altitude, 'f', 6);
			QString print_Heading = QString::number(m_beidou_info.Heading, 'f', 6);
			ShowLineText(1, QStringLiteral("定位定向"), QStringLiteral("经度：%1，纬度%2，高度%3，北向方位：%4").arg(print_Longitude).arg(print_Latitude).arg(print_Altitude).arg(print_Heading));//打印字符串
			break;
		}
		default:
			break;
		}
	}
	if (m_pic_up_realtime_state.VIfocuesValue == 0 || m_pic_up_realtime_state.VIfocuesValue==65535)
	{
		m_pic_up_realtime_state.VIfocuesValue = last_vi_focus;
	}
	else
	{
		last_vi_focus = m_pic_up_realtime_state.VIfocuesValue;
	}
	if (m_pic_up_realtime_state.IRfocuesValue == 0 || m_pic_up_realtime_state.IRfocuesValue == 65535)
	{
		m_pic_up_realtime_state.IRfocuesValue = last_ir_focus;
	}
	else
	{
		last_vi_focus = m_pic_up_realtime_state.IRfocuesValue;
	}



	//qDebug()<<sizeof(DcMsgUp);
}
float fzqjMain_user::degToRad(float deg)
{
	return deg * (M_PI / 180.0);
}
float fzqjMain_user::radToDeg(float rad)
{
	return rad * ( 180.0/ M_PI);
}
void fzqjMain_user::OnScreenClick_VL_left(int x, int y)
{
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	if (m_pic_up_realtime_state.VIshichang_X > 4000 | m_pic_up_realtime_state.VIshichang_X < 10)
	{
		return;
	}
	m_xk_down_msg.msg_type = E_FK_SF_MOVE_TO;
	int width = ui.label_videodisplay_vl->width();
	int height = ui.label_videodisplay_vl->height();
	float fov_x = m_pic_up_realtime_state.VIshichang_X / 100.0;
	float fov_y = m_pic_up_realtime_state.VIshichang_Y / 100.0;
	//float fov_x = 3.29;
	//float fov_y = 1.85;
	float current_fw = m_pic_up_realtime_state.fw/1000.0;
	float current_fy = m_pic_up_realtime_state.fy/1000.0;

	double diff_x;
	double diff_y;
	calculateDeltaAngles(x, y, width, height, 1920, 1080, fov_x, fov_y, current_fw, current_fy,diff_x, diff_y);
	diff_x = diff_x * 1000;

	diff_y = diff_y * 1000;
	if (diff_x > 360000)
	{
		diff_x -= 360000;
	}
	if (diff_x < 0)
	{
		diff_x += 360000;
	}

	//double realx = x * picLeftPraW / (double)width;
	//double realy = y * picLeftPraH / (double)height;
	//float realfw = (realx - picLeftPraW / 2) / picLeftPraW * (m_pic_up_realtime_state.VIshichang_X * 10);
	//float realfy = (realy - picLeftPraH / 2) / picLeftPraH * (m_pic_up_realtime_state.VIshichang_Y * 10);
	//int fw = m_pic_up_realtime_state.fw + realfw;
	//int fy = m_pic_up_realtime_state.fy - realfy;
	//if (fw > 360000)
	//{
	//	fw -= 360000;
	//}
	//if (fw < 0)
	//{
	//	fw += 360000;
	//}
	m_xk_down_msg.param_1 = diff_x;
	m_xk_down_msg.param_2 = diff_y;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("转台-移动到点选位置");
	ShowLineText(0, 0, str);
	//DSP检测指定位置
	m_xk_down_msg.msg_type = E_FK_AUTO_DETECT_ONE_VL;
	m_xk_down_msg.param_1 = 960;
	m_xk_down_msg.param_2 = 540;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	b_yaogan_mainCamera = false;
	SetMainCamera(b_yaogan_mainCamera);
	ui.lb_mainvideo->setText(QStringLiteral("可见光"));
	is_main_camera = 0;
}

void fzqjMain_user::calculateDeltaAngles(
	double u_d, double v_d, // 鼠标点击位置在显示框中的坐标
	double W_d, double H_d, // 显示框的宽高
	double W, double H, // 相机分辨率
	double fov_h, double fov_v, // 相机的水平和垂直视场角（度）
	double theta_0, double phi_0, // 当前方位角和俯仰角（度）
	double& deltaTheta, double& deltaPhi // 输出的跳转角度（度）
) {
	// 将显示框坐标转换为图像坐标
	double u = (u_d / W_d) * W;
	double v = (v_d / H_d) * H;

	// 计算点击位置相对于图像中心的偏移量
	double delta_u = u - W / 2;
	double delta_v = v - H / 2;

	// 将视场角从度转换为弧度
	double fov_h_rad = degToRad(fov_h);
	double fov_v_rad = degToRad(fov_v);

	// 归一化处理
	double norm_u = delta_u / (W / 2);
	double norm_v = delta_v / (H / 2);

	// 计算点击位置的方向角度（透视投影修正）
	double theta_click = atan2(norm_u, 1 / tan(fov_h_rad / 2));
	double phi_click = -atan2(norm_v, 1 / tan(fov_v_rad / 2));

	// 计算新的方位角和俯仰角
	double theta_new = degToRad(theta_0) + theta_click;
	double phi_new = degToRad(phi_0) + phi_click;

	deltaTheta = radToDeg(theta_new);
	deltaPhi = radToDeg(phi_new);
}
void fzqjMain_user::OnScreenClick_VL_Right(int x, int y)
{
	if (m_pic_up_realtime_state.dsp1_mode)
	{
		on_btn_sf_exit_track_2_clicked();
	}
	else
	{
		QString str = QStringLiteral("可见光-目标跟踪");
		ShowLineText(0, 0, str);
		SetMainCamera(false);
		ui.lb_mainvideo->setText(QStringLiteral("可见光"));
		m_xk_down_msg.msg_type = E_FK_AUTO_TRACK_ONE_VL;
		int width = ui.label_videodisplay_vl->width();
		int height = ui.label_videodisplay_vl->height();
		double rateW = picLeftPraW / (double)width;
		double rateH = picLeftPraH / (double)height;
		m_xk_down_msg.param_1 = x * rateW;
		m_xk_down_msg.param_2 = y * rateH;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
		qDebug() << "track press:" << m_xk_down_msg.param_1 << ":" << m_xk_down_msg.param_2;
		is_main_camera = 0;
	}
}

void fzqjMain_user::OnScreenClick_IR_left(int x, int y)
{
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	if (m_pic_up_realtime_state.IRshichang_X > 800 | m_pic_up_realtime_state.IRshichang_X < 10)
	{
		return;
	}
	m_xk_down_msg.msg_type = E_FK_SF_MOVE_TO;
	//int width = ui.label_videodisplay_ir->width();
	//int height = ui.label_videodisplay_ir->height();
	//double realx = x * 640 / (double)width;
	//double realy = y * 512 / (double)height;
	//float realfw = (realx - 640 / 2) / 640 * (m_pic_up_realtime_state.IRshichang_X * 10);
	//float realfy = (realy - 512 / 2) / 512 * (m_pic_up_realtime_state.IRshichang_Y * 10);
	//int fw = m_pic_up_realtime_state.fw + realfw;
	//int fy = m_pic_up_realtime_state.fy - realfy;
	//if (fw > 360000)
	//{
	//	fw -= 360000;
	//}
	//if (fw < 0)
	//{
	//	fw += 360000;
	//}
	int width = ui.label_videodisplay_ir->width();
	int height = ui.label_videodisplay_ir->height();
	float fov_x = m_pic_up_realtime_state.IRshichang_X / 100.0;
	float fov_y = m_pic_up_realtime_state.IRshichang_Y / 100.0;
	//float fov_x = 3.29;
	//float fov_y = 1.85;
	float current_fw = m_pic_up_realtime_state.fw / 1000.0;
	float current_fy = m_pic_up_realtime_state.fy / 1000.0;

	double diff_x;
	double diff_y;
	calculateDeltaAngles(x, y, width, height, 640, 512, fov_x, fov_y, current_fw, current_fy, diff_x, diff_y);
	diff_x = diff_x * 1000;

	diff_y = diff_y * 1000;
	if (diff_x > 360000)
	{
		diff_x -= 360000;
	}
	if (diff_x < 0)
	{
		diff_x += 360000;
	}
	m_xk_down_msg.param_1 = diff_x;
	m_xk_down_msg.param_2 = diff_y;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("转台-移动到点选位置");
	ShowLineText(0, 0, str);
	//DSP检测指定位置
	m_xk_down_msg.msg_type = E_FK_AUTO_DETECT_ONE_IR;
	m_xk_down_msg.param_1 = 320;
	m_xk_down_msg.param_2 = 256;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	b_yaogan_mainCamera = true;
	SetMainCamera(b_yaogan_mainCamera);
	ui.lb_mainvideo->setText(QStringLiteral("红外"));
	is_main_camera = 1;
}

void fzqjMain_user::OnScreenClick_IR_Right(int x, int y)
{
	if (m_pic_up_realtime_state.dsp2_mode)
	{
		on_btn_sf_exit_track_2_clicked();
	}
	else
	{
		QString str = QStringLiteral("红外-目标跟踪");
		ShowLineText(0, 0, str);
		SetMainCamera(true);
		ui.lb_mainvideo->setText(QStringLiteral("红外"));
		m_xk_down_msg.msg_type = E_FK_AUTO_TRACK_ONE_IR;
		int width = ui.label_videodisplay_ir->width();
		int height = ui.label_videodisplay_ir->height();
		double rateW = 640 / (double)width;
		double rateH = 512 / (double)height;
		m_xk_down_msg.param_1 = x * rateW;
		m_xk_down_msg.param_2 = y * rateH;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
		qDebug() << "track press:" << m_xk_down_msg.param_1 << ":" << m_xk_down_msg.param_2;
		is_main_camera = 1;
	}
}


void fzqjMain_user::on_toolButton_savevideo_start_clicked(void)
{
	if (!bRecording)
	{
		if (vi_Record == nullptr && Ir_Record == nullptr)
		{
			return;
		}
		QString str = QStringLiteral("系统控制-视频存储-开始");
		ShowLineText(0, 0, str);


		QDateTime curDateTime = QDateTime::currentDateTime();
		QString recordFileNameVi = QStringLiteral("%1/%2%3.mp4").arg(m_xk_configinfo.VIDEO_SAVE_Addr).arg(curDateTime.toString("yyyy-MM-dd-hh-mm-ss")).arg("_VI");

		ui.toolButton_savevideo_start->setText(QStringLiteral("..."));
		SetBtnHighLight(ui.toolButton_savevideo_start, true);
		emit Sig_VI_Record_Start(recordFileNameVi);

		QString recordFileNameIr = QStringLiteral("%1/%2%3.mp4").arg(m_xk_configinfo.VIDEO_SAVE_Addr).arg(curDateTime.toString("yyyy-MM-dd-hh-mm-ss")).arg("_IR");
		emit Sig_Ir_Record_Start(recordFileNameIr);
		bRecording = true;
	}

}

void fzqjMain_user::on_toolButton_savevideo_stop_clicked(void)
{
	QString str = QStringLiteral("系统控制-视频存储-结束");
	ShowLineText(0, 0, str);
	vi_Record->Stop();
	Ir_Record->Stop();
	ui.toolButton_savevideo_start->setText(QStringLiteral("开始"));
	SetBtnHighLight(ui.toolButton_savevideo_start, false);
	bRecording = false;
}

void fzqjMain_user::on_btn_ai_open_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_OPEN_TARGET_DISTINGUISH;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("系统控制-目标识别-开");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_ai_close_clicked(void)
{
	warningSound->stop();
	m_xk_down_msg.msg_type = E_FK_CLOSE_TARGET_DISTINGUISH;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("系统控制-目标识别-关");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_set_sysinfo_clicked(void)
{
	QString str = QStringLiteral("系统控制-专家设置-打开");
	ShowLineText(0, 0, str);
	bool Is_Windows_Open = is_windows_open("fzqjSysInfo");

	if (Is_Windows_Open == false)
	{
		return;
	}
	else
	{
		fzqjSysInfo* w = new fzqjSysInfo();
		w->m_configManager = m_configManager;
		w->m_xk_down_config = m_xk_down_config;
		w->m_xk_down_msg = m_xk_down_msg;
		connect(w, SIGNAL(sig_sendMsg2Pic(XKDownMsg)), this, SLOT(sendMsg2Pic(XKDownMsg)));
		connect(w, SIGNAL(sig_sendConfig2Pic(XKDownConfig)), this, SLOT(sendConfig2Pic(XKDownConfig)));
		connect(w, SIGNAL(sig_InitConfigInfo(XKConfigInfo)), this, SLOT(InitConfigInfo(XKConfigInfo)));
		connect(this, SIGNAL(sig_RefreshGDConfig(GDConfigInfo)), w, SLOT(RefreshGDConfig(GDConfigInfo)));
		connect(w, &fzqjSysInfo::sigUpdatepixnums, this, &fzqjMain_user::updatePixNumAll);
		connect(w, &fzqjSysInfo::sigReboot, this, &fzqjMain_user::gdRebootSend);
		connect(w, &fzqjSysInfo::sigWatchDogMsg, this, &fzqjMain_user::setWatchDog);
		w->setAttribute(Qt::WA_DeleteOnClose, true);
		w->show();
	}
}

void fzqjMain_user::vl_auto_track(void)
{
	QString str = QStringLiteral("可见光-跟踪-自动");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_AUTO_TRACK_AUTO_VL;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vl_all_track(void)
{
	QString str = QStringLiteral("可见光-跟踪-全帧");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_AUTO_TRACK_ALL_VL;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_ir_auto_track_clicked(void)
{
	QString str = QStringLiteral("红外-跟踪-自动");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_AUTO_TRACK_AUTO_IR;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_ir_all_track_clicked(void)
{
	QString str = QStringLiteral("红外-跟踪-全帧");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_AUTO_TRACK_ALL_IR;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_dsp_open_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_OPEN_TARGET_CHECK;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	on_btn_ir_osd_open_clicked();
	vl_osd_open();
	QString str = QStringLiteral("系统控制-目标检测-开");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_dsp_close_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_CLOSE_TARGET_CHECK;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	on_btn_ir_osd_close_clicked();
	vl_osd_close();
	QString str = QStringLiteral("系统控制-目标检测-关");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::OncloseToolBtn(void)
{
	if (QMessageBox::question(NULL, QStringLiteral("提示"), QStringLiteral("确定关闭该软件？")) == QMessageBox::Yes)
	{
		this->close();
	}
}

void fzqjMain_user::OnmaximizeToolBtn(void)
{
	if (b_isFullWindow)
	{
		showNormal();
	}
	else
	{
		showFullScreen();
	}
	b_isFullWindow = !b_isFullWindow;
}

void fzqjMain_user::OnminimizeToolBtn(void)
{
	showMinimized();
}

void fzqjMain_user::OnImageViewResizeL(int a, int b)
{
	if ((float)ui.groupBox->height() / (float)ui.groupBox->width() > picLeftPraH / picLeftPraW)
	{
		ui.label_videodisplay_vl->setMinimumWidth(ui.groupBox->width() - 50);
		ui.label_videodisplay_vl->setMinimumHeight(ui.label_videodisplay_vl->width() * picLeftPraH / picLeftPraW);
	}
	else
	{
		ui.label_videodisplay_vl->setMinimumHeight(ui.groupBox->height() - 50);
		ui.label_videodisplay_vl->setMinimumWidth(ui.label_videodisplay_vl->height() / picLeftPraH / picLeftPraW);
	}
	// showFullScreen();
}

void fzqjMain_user::on_btn_clear_recvText_clicked(void)
{
	QString str = QStringLiteral("信息栏-清空");
	ShowLineText(0, 0, str);
	ui.textBrowser_2->clear();
}

void fzqjMain_user::on_btn_Lidar_YinDao_Focus_clicked(void)
{
	if (is_guideing ==false)
	{
		ui.btn_Lidar_YinDao_Focus->setText(QStringLiteral("自动变焦中..."));
		SetBtnHighLight(ui.btn_Lidar_YinDao_Focus, true);
		m_configManager->set("IS_GUIDE_ADAPT_VIEW", "1");
		m_configManager->print("Config.ini");
		is_guideing = true;
		m_timer500->start();
	}
	else if (is_guideing == true)
	{
		ui.btn_Lidar_YinDao_Focus->setText(QStringLiteral("引导自动变焦"));
		SetBtnHighLight(ui.btn_Lidar_YinDao_Focus, false);
		m_configManager->set("IS_GUIDE_ADAPT_VIEW", "0");
		m_configManager->print("Config.ini");
		is_guideing = false;
		
		m_timer500->stop();
	}
}

void fzqjMain_user::on_btn_auto_track_open_clicked(void)
{
	//可见光
	if (is_main_camera ==0)
	{
		vl_auto_track();
	}
	//红外
	else if (is_main_camera == 1)
	{
		on_btn_ir_auto_track_clicked();
	}
}

void fzqjMain_user::on_btn_auto_track_close_clicked(void)
{
	on_btn_sf_exit_track_2_clicked();
	on_btn_ai_close_clicked();
}

void fzqjMain_user::on_btn_open_dis_clicked(void)
{
	ui.btn_start_1_dis_2->setEnabled(true);
	ui.btn_start_more_dis->setEnabled(true);
}


void fzqjMain_user::on_btn_devState_Lidar_clicked(void)
{
	isGetLeiDaYinDao = !isGetLeiDaYinDao;
	if (isGetLeiDaYinDao)
	{
		/*vl_auto_track();
		on_btn_ir_auto_track_clicked();*/
		ui.btn_devState_Lidar->setText(QStringLiteral("引导中..."));
		SetBtnHighLight(ui.btn_devState_Lidar, true);
		QString str = QStringLiteral("雷达引导-开始");
		ShowLineText(0, 0, str);
	}
	else
	{
		on_btn_sf_exit_track_2_clicked();
		ui.btn_devState_Lidar->setText(QStringLiteral("雷达引导"));
		SetBtnHighLight(ui.btn_devState_Lidar, false);
		QString str = QStringLiteral("雷达引导-结束");
		ShowLineText(0, 0, str);
	}
}

void fzqjMain_user::on_btn_manual_target_send_clicked(void)
{
	QString str = QStringLiteral("手动上报-打开");
	ShowLineText(0, 0, str);
	bool Is_Windows_Open = is_windows_open("fzqjReport");
	if (Is_Windows_Open == false)
	{
		return;
	}
	else {

		XKUpDevStateMsg manualTarget = m_xk_up_devState;
		manualTarget.devstate = 0;
		manualTarget.TS = QDateTime::currentDateTime().toMSecsSinceEpoch();
		manualTarget.ztAz = (double)m_pic_up_realtime_state.fw / 100.0;//小数点目标3位，上报1位
		manualTarget.ztPc = (double)m_pic_up_realtime_state.fy / 100.0;
		if (is_main_camera == 0)
		{
			m_xk_up_devState.view_Zoom = m_pic_up_realtime_state.VIfocuesValue * 10;
		}
		else if (is_main_camera == 1)
		{
			m_xk_up_devState.view_Zoom = m_pic_up_realtime_state.IRfocuesValue * 10;
		}
		manualTarget.pixel_nums = 0;
		manualTarget.Lon = jingdu * 1000000;//
		manualTarget.Lat = weidu * 1000000;//
		manualTarget.Alt = gaodu * 100;//
		manualTarget.trackState = 1;//trackState
		manualTarget.targetAz = (m_pic_up_realtime_state.fw / 100) - biaojiaoleida_fw * 10;//
		manualTarget.targetPc = (m_pic_up_realtime_state.fy / 100) - biaojiaoleida_fy * 10;//
		manualTarget.targetDis = m_pic_up_realtime_state.fake_distance;//
		//manualTarget.devID = m_xk_up_devState.devID;
		for (int i = 0; i < 20; i++)
		{
			manualTarget.devID[i] = m_xk_up_devState.devID[i];
		}
		manualTarget.sourceID = m_xk_up_devState.sourceID;
		if (target_manul_type != 0)//
		{
			manualTarget.targetType = target_manul_type - 1;//0为自动，手动选择从1开始
		}
		else
		{
			int temp_Type = m_pic_up_realtime_state.AI_target_type_VL ? m_pic_up_realtime_state.AI_target_type_VL : m_pic_up_realtime_state.AI_target_type_IR;
			switch (temp_Type)
			{
			case 0:
				manualTarget.targetType = FK_TARGET_UNKNOWN;
				break;
			case 1:
				manualTarget.targetType = FK_TARGET_XUANYI_WRJ;
				break;
			case 2:
				manualTarget.targetType = FK_TARGET_GUDINGYI_WRJ;
				break;
			case 3:
				manualTarget.targetType = FK_TARGET_ZHISHENG;
				break;
			case 4:
				manualTarget.targetType = FK_TARGET_KONGPIAOWU;
				break;
			case 5:
				manualTarget.targetType = FK_TARGET_KONGPIAOWU;
				break;
			case 6:
				manualTarget.targetType = FK_TARGET_MINHANG;
			default:
				break;
			}
		}
		fzqjReport* w = new fzqjReport();
		w->manualTarget = manualTarget;
		w->init_windows();
		connect(w, SIGNAL(sig_report_send(XKUpDevStateMsg)), this, SLOT(sendReportMsg(XKUpDevStateMsg)));
		w->setAttribute(Qt::WA_DeleteOnClose, true);
		w->show();
	}
}

void fzqjMain_user::on_btn_stop_dis_2_clicked(void)
{
	//关闭定时器-关闭连续测距使能
	m_bLaserDisStart = false;
	ui.btn_start_more_dis->setText(QStringLiteral("连续测距"));
	SetBtnHighLight(ui.btn_start_more_dis, false);
	ui.btn_start_1_dis_2->setEnabled(false);
	ui.btn_start_more_dis->setEnabled(false);
}

void fzqjMain_user::on_btn_start_1_dis_2_clicked(void)
{
	QString str = QStringLiteral("激光测距-单次测距");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_LASER_RANGING_ONE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}
void fzqjMain_user::on_btn_start_more_dis_clicked(void)//5hz
{
	if (!m_bLaserDisStart)
	{
		//打开定时器-打开连续测距使能
		m_bLaserDisStart = true;
		//按钮高亮
		ui.btn_start_more_dis->setText(QStringLiteral("测距中.."));
		SetBtnHighLight(ui.btn_start_more_dis, true);
		QString str = QStringLiteral("激光测距-连续测距-开始");
		ShowLineText(0, 0, str);
	}
	else
	{
		//关闭定时器-关闭连续测距使能
		QString str = QStringLiteral("激光测距-连续测距-结束");
		ShowLineText(0, 0, str);
		m_bLaserDisStart = false;
		ui.btn_start_more_dis->setText(QStringLiteral("连续测距"));
		SetBtnHighLight(ui.btn_start_more_dis, false);
	}
}

void fzqjMain_user::on_btnMid_pressed(void)
{
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	m_xk_down_msg.msg_type = E_FK_SF_MOVE_TO;
	m_xk_down_msg.param_1 = m_pic_up_realtime_state.fw;
	m_xk_down_msg.param_2 = m_pic_up_realtime_state.fy;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btnMid_released(void)
{
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_stop_clicked(void)
{
	QString str = QStringLiteral("伺服转台-刹车");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		m_xk_down_msg.msg_type = E_FK_EXIT_TRACK;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
	}
	m_xk_down_msg.msg_type = E_FK_SF_STOP;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btnLT_pressed(void)
{
	QString str = QStringLiteral("转台-左上运动-开始");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	float xspeed = (float)ui.Slider_speedx->value();
	float yspeed = (float)ui.Slider_speedy->value();
	int16_t _x = -1 * xspeed;
	int16_t _y = yspeed;
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = _x;
	m_xk_down_msg.param_2 = _y;
	sendMsg2Pic();
}

void fzqjMain_user::on_btnLT_released(void)
{
	sendSFshache();
	QString str = QStringLiteral("转台-左上运动-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btnTop_pressed(void)
{
	QString str = QStringLiteral("转台-向上运动-开始");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	float yspeed = (float)ui.Slider_speedy->value();
	int16_t _x = 0;
	int16_t _y = yspeed;
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = _x;
	m_xk_down_msg.param_2 = _y;
	sendMsg2Pic();
}

void fzqjMain_user::on_btnTop_released(void)
{
	sendSFshache();
	QString str = QStringLiteral("转台-向上运动-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btnRT_pressed(void)
{
	QString str = QStringLiteral("转台-右上运动-开始");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	float xspeed = (float)ui.Slider_speedx->value();
	float yspeed = (float)ui.Slider_speedy->value();
	int16_t _x = 1 * xspeed;
	int16_t _y = 1 * yspeed;
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = _x;
	m_xk_down_msg.param_2 = _y;
	sendMsg2Pic();
}

void fzqjMain_user::on_btnRT_released(void)
{
	sendSFshache();
	QString str = QStringLiteral("转台-右上运动-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btnRight_pressed(void)
{
	QString str = QStringLiteral("转台-向右运动-开始");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	float xspeed = (float)ui.Slider_speedx->value();
	int16_t _x = 1 * xspeed;
	int16_t _y = 0;
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = _x;
	m_xk_down_msg.param_2 = _y;
	sendMsg2Pic();
}

void fzqjMain_user::on_btnRight_released(void)
{
	sendSFshache();
	QString str = QStringLiteral("转台-向右运动-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btnRB_pressed(void)
{
	QString str = QStringLiteral("转台-右下运动-开始");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	float xspeed = (float)ui.Slider_speedx->value();
	float yspeed = (float)ui.Slider_speedy->value();
	int16_t _x = 1 * xspeed;
	int16_t _y = -1 * yspeed;
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = _x;
	m_xk_down_msg.param_2 = _y;
	sendMsg2Pic();
}

void fzqjMain_user::on_btnRB_released(void)
{
	sendSFshache();
	QString str = QStringLiteral("转台-右下运动-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btnBottom_pressed(void)
{
	QString str = QStringLiteral("转台-向下运动-开始");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	float yspeed = (float)ui.Slider_speedy->value();
	int16_t _x = 0;
	int16_t _y = -1 * yspeed;
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = _x;
	m_xk_down_msg.param_2 = _y;
	sendMsg2Pic();
}

void fzqjMain_user::on_btnBottom_released(void)
{
	sendSFshache();
	QString str = QStringLiteral("转台-向下运动-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btnLB_pressed(void)
{
	QString str = QStringLiteral("转台-左下运动-开始");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	float xspeed = (float)ui.Slider_speedx->value();
	float yspeed = (float)ui.Slider_speedy->value();
	int16_t _x = -1 * xspeed;
	int16_t _y = -1 * yspeed;
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = _x;
	m_xk_down_msg.param_2 = _y;
	sendMsg2Pic();
}

void fzqjMain_user::on_btnLB_released(void)
{
	sendSFshache();
	QString str = QStringLiteral("转台-左下运动-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btnLeft_pressed(void)
{
	QString str = QStringLiteral("转台-向左运动-开始");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	float xspeed = (float)ui.Slider_speedx->value();
	int16_t _x = -1 * xspeed;
	int16_t _y = 0;
	m_xk_down_msg.msg_type = E_FK_SF_MOVE;
	m_xk_down_msg.param_1 = _x;
	m_xk_down_msg.param_2 = _y;
	sendMsg2Pic();
}

void fzqjMain_user::on_btnLeft_released(void)
{
	sendSFshache();
	QString str = QStringLiteral("转台-向左运动-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::btn_vl_black_target(void)
{
	QString str = QStringLiteral("可见光-目标特征-暗");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VL_BLACK_TARGET;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::btn_vl_write_target(void)
{
	QString str = QStringLiteral("可见光-目标特征-亮");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VL_WRITE_TARGET;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_vl_dbd_plus_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_CONTRAST_INCREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-增益加");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_vl_dbd_minus_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_CONTRAST_DECREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-增益减");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_selfCheck_clicked(void)
{
	if (!b_pingPic)
	{
		QString checkStr = QStringLiteral("设备未连接！");
		ShowLineText(1, QStringLiteral("自检"), checkStr);
		{
			m_logSelfCheck->writeLog(checkStr.toStdString());
		}
		return;
	}
	QString checkStr = QStringLiteral("指令发送");
	ShowLineText(1, QStringLiteral("自检"), checkStr);//打印发送时间
	bPrintSelfCheckTime = true;
	m_xk_down_msg.msg_type = E_FK_SYS_SELFCHECK;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}


QString fzqjMain_user::int8C_to_StateInfo(int8_t in_state)
{
	QString normal = QStringLiteral("正常");
	QString falut = QStringLiteral("故障");
	if (in_state == 0)
	{
		return falut;
	}
	return normal;
}
QString fzqjMain_user::int8C_to_OpenorClose(int8_t in_state)
{
	QString normal = QStringLiteral("打开");
	QString falut = QStringLiteral("关闭");
	if (in_state == 0)
	{
		return falut;
	}
	return normal;
}

QString fzqjMain_user::bool_to_StateInfo(bool in_bool)
{
	QString normal = QStringLiteral("打开");
	QString falut = QStringLiteral("关闭");
	if (in_bool == false)
	{
		return falut;
	}
	return normal;
}

void fzqjMain_user::on_btn_save_realtimeMsg_clicked(void)
{
	QString str = QStringLiteral("系统控制-参数保存-保存实时报文");
	ShowLineText(0, 0, str);
	m_bSaveRealTimeMsg = !m_bSaveRealTimeMsg;

	if (m_bSaveRealTimeMsg)
	{
		string RealStr = m_xk_configinfo.LOG_SAVE_Addr;
		RealStr.append("\\LOG_REALTIME");
		m_logRealTime = new LogInfo(1024 * 10, RealStr);
		m_logRealTime->start();
		ui.btn_save_realtimeMsg->setText(QStringLiteral("结束保存报文"));
		SetBtnHighLight(ui.btn_save_realtimeMsg, true);
	}
	else
	{
		//关闭
		m_logRealTime->stop();
		ui.btn_save_realtimeMsg->setText(QStringLiteral("保存实时报文"));
		SetBtnHighLight(ui.btn_save_realtimeMsg, false);
		m_logRealTime = new LogInfo(1024 * 10, "");
	}
}

void fzqjMain_user::on_btn_save_selfCheckMsg_clicked(void)
{
	m_bSaveSelfCheckMsg = !m_bSaveSelfCheckMsg;
	if (m_bSaveSelfCheckMsg)
	{
		m_logSelfCheck->start();
	}
	else
	{
		//关闭
		m_logSelfCheck->stop();
	}
}

void fzqjMain_user::on_btn_vl_v_add_pressed(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_ZOOM_INCREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-视场小-开始");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_vl_v_add_released(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-视场小-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::vl_zk_stop(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-视场/调焦-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_vl_v_add_mini_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_ZOOM_INCREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	cv::waitKey(200);
	m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_vl_v_nadd_pressed(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_ZOOM_DECREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-视场大-开始");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_vl_v_nadd_released(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-视场大-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_vl_v_nadd_mini_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_ZOOM_DECREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	cv::waitKey(200);
	m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}


void fzqjMain_user::on_btn_ir_v_add_pressed(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_ZOOM_INCREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("红外-视场小-开始");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_ir_v_add_released(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("红外-视场小-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::ir_zk_stop(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("红外-视场/调焦-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_ir_v_add_mini_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_ZOOM_INCREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	cv::waitKey(200);
	m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_ir_v_nadd_pressed(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_ZOOM_DECREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("红外-视场大-开始");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_ir_v_nadd_released(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("红外-视场大-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_ir_v_nadd_mini_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_ZOOM_DECREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	cv::waitKey(200);
	m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_manual_clicked(void)
{
	int xspeed = ui.Slider_speedx->value();
	int yspeed = ui.Slider_speedy->value();
	sendMsg2Pic();
}

void fzqjMain_user::on_Slider_speedx_valueChanged(int value)
{
	ui.label_speedx_2->setText(QString::number((double)value / 100, 'f', 2));
}

void fzqjMain_user::on_Slider_speedy_valueChanged(int value)
{
	ui.label_speedy_2->setText(QString::number((double)value / 100, 'f', 2));
}

void fzqjMain_user::sf_close(void)
{
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	m_xk_down_msg.msg_type = E_FK_SF_CLOSE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_track_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_AUTO_TRACK_ONE_TARGET;
	m_xk_down_msg.param_1 = 0;
	m_xk_down_msg.param_2 = 0;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_exit_track_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_EXIT_TRACK;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_exit_track_2_clicked(void)
{
	QString str = QStringLiteral("目标跟踪-退出");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_EXIT_TRACK;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	m_xk_down_msg.msg_type = E_FK_SF_STOP;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_vl_focue_add_pressed(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_FOCUSING_INCREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-调焦加-开始");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_vl_focue_add_released(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-调焦加-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_vl_focue_add_mini_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_FOCUSING_INCREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	cv::waitKey(200);
	m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_vl_focuse_minus_pressed(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_FOCUSING_DECREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-调焦减-开始");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_vl_focuse_minus_released(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("可见光-调焦减-结束");
	ShowLineText(0, 0, str);
}
void fzqjMain_user::on_btn_vl_focuse_minus_mini_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_FOCUSING_DECREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	cv::waitKey(200);
	m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}
void fzqjMain_user::on_btn_vl_auto_focuse_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_AUTO_FOCUSING;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}



void fzqjMain_user::on_btn_ir_focue_add_pressed(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_FOCUSING_INCREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("红外-调焦加-开始");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_ir_focue_add_released(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("红外-调焦加-结束");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_ir_focue_add_mini_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_FOCUSING_INCREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	cv::waitKey(200);
	m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_ir_focuse_minus_pressed(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_FOCUSING_DECREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("红外-调焦减-开始");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_ir_focuse_minus_released(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("红外-调焦减-结束");
	ShowLineText(0, 0, str);
}
void fzqjMain_user::on_btn_ir_focuse_minus_mini_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_FOCUSING_DECREASES;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	cv::waitKey(200);
	m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}
void fzqjMain_user::on_btn_ir_auto_focuse_clicked(void)
{
	QString str = QStringLiteral("红外-自动调焦-触发");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_AUTO_FOCUSING;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

static double last_sdsy_fw = 0;
void fzqjMain_user::sf_shuyin(double in_sfx, double in_sfy)
{
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	//判断是否正确数值
	vector<double> errorDataList;
	if (in_sfx < 0 || in_sfx > 360)
	{
		errorDataList.push_back(in_sfx);
	}
	if (in_sfy < -50 || in_sfy > 90)
	{
		errorDataList.push_back(in_sfy);
	}
	if (errorDataList.size() > 0)
	{
		for (int i = 0; i < errorDataList.size(); i++)
		{
			QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("非法的数值: \"%1\"").arg(errorDataList[i]));
		}
		return;
	}
	int x =(int)(in_sfx * 1000);
	int y = (int)(in_sfy * 1000);
	m_xk_down_msg.msg_type = E_FK_SF_MOVE_TO;
	m_xk_down_msg.param_1 = x;
	m_xk_down_msg.param_2 = y;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;

	if (last_sdsy_fw == 0)
	{
		last_sdsy_fw = in_sfx;
		//转台控制
		if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
		{
			qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
			return;
		}
		x =(int)(in_sfx * 1000);
		y =(int)(in_sfy * 1000);
		m_xk_down_msg.msg_type = E_FK_SF_MOVE_TO;
		m_xk_down_msg.param_1 = x;
		m_xk_down_msg.param_2 = y;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
	}
	else
	{
		if (last_sdsy_fw - m_pic_up_realtime_state.fw / 1000 > 20)
		{
			int a = 1;
		}
		else
		{
			last_sdsy_fw = 0;
		}
	}
}

void fzqjMain_user::on_btn_sf_shuyin_clicked(void)
{
	QString str = QStringLiteral("转台-运动-跳转到：方位%1、俯仰：%2").arg(ui.doubleSpinBox_sfx->value()).arg(ui.doubleSpinBox_sfy->value());
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	float in_sfx = ui.doubleSpinBox_sfx->value();
	float in_sfy = ui.doubleSpinBox_sfy->value();
	//判断是否正确数值
	vector<double> errorDataList;
	if (in_sfx < 0 || in_sfx > 360)
	{
		errorDataList.push_back(in_sfx);
	}
	if (in_sfy < -50 || in_sfy > 90)
	{
		errorDataList.push_back(in_sfy);
	}
	if (errorDataList.size() > 0)
	{
		for (int i = 0; i < errorDataList.size(); i++)
		{
			QMessageBox::warning(0, QStringLiteral("错误："), QStringLiteral("非法的数值: \"%1\"").arg(errorDataList[i]));
		}
		return;
	}
	int x =(int)(in_sfx * 1000);
	int y =(int)(in_sfy * 1000);
	m_xk_down_msg.msg_type = E_FK_SF_MOVE_TO;
	m_xk_down_msg.param_1 = x;
	m_xk_down_msg.param_2 = y;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;

	if (last_sdsy_fw == 0)
	{
		last_sdsy_fw = in_sfx;
		//转台控制
		if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
		{
			qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
			return;
		}
		x = (int)(in_sfx * 1000);
		y = (int)(in_sfy * 1000);
		m_xk_down_msg.msg_type = E_FK_SF_MOVE_TO;
		m_xk_down_msg.param_1 = x;
		m_xk_down_msg.param_2 = y;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
	}
	else
	{
		if (last_sdsy_fw - m_pic_up_realtime_state.fw / 1000 > 20)
		{
			int a = 1;
		}
		else
		{
			last_sdsy_fw = 0;
		}
	}
}

void fzqjMain_user::on_btn_vl_luma_set_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_LUMA_SET_LEVEL;
	m_xk_down_msg.param_1 = ui.txt_luma_value->value();
	sendMsg2Pic();
	ui.lb_mainvideo->setText(QStringLiteral("可见光"));
	QString str = QStringLiteral("可见光--光圈设置为：%1").arg(ui.txt_luma_value->value());
	ShowLineText(0, 0, str);
}

void fzqjMain_user::btn_vl_qw_open(int level)
{

	QString str = QStringLiteral("可见光-去雾等级-设置为：%1").arg(level);
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VL_DEHAZE_OPEN;
	m_xk_down_msg.param_1 = level;
	sendMsg2Pic();
	ui.lb_mainvideo->setText(QStringLiteral("可见光"));
}

void fzqjMain_user::on_btn_vl_qw_close_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_DEHAZE_CLOSE;
	sendMsg2Pic();
}

void fzqjMain_user::pic_improve_open_L(void)
{
	QString str = QStringLiteral("红外-图像增强-低");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_IMAGE_ENHANCEMENT_1;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::pic_improve_open_M(void)
{
	QString str = QStringLiteral("红外-图像增强-中");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_IMAGE_ENHANCEMENT_2;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::pic_improve_open_H(void)
{
	QString str = QStringLiteral("红外-图像增强-高");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_IMAGE_ENHANCEMENT_3;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::ir_manul_correction(void)
{
	QString str = QStringLiteral("红外-手动校准正-触发");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_MANUL_CORRECTION;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::ir_send_clicked(QByteArray data)
{
	QString str = QStringLiteral("红外-自定义指令-下发");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_SEND_CUSTOMDATA;
	m_xk_down_msg.param_1 = data.size();
	memcpy(((byte*)&m_xk_down_msg) + 7, data, data.size());
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_ir_more_clicked(void)
{
	bool Is_Windows_Open = is_windows_open("fzqjIrMore");
	QString str = QStringLiteral("红外-专家设置-打开");
	ShowLineText(0, 0, str);
	if (Is_Windows_Open == false)
	{
		return;
	}
	else
	{
		fzqjIrMore* w = new fzqjIrMore();
		connect(w, SIGNAL(sig_ir_manul_correction()), this, SLOT(ir_manul_correction()));
		connect(w, SIGNAL(sig_ir_send_clicked(QByteArray)), this, SLOT(ir_send_clicked(QByteArray)));
		connect(w, SIGNAL(sig_pic_improve_open_L()), this, SLOT(pic_improve_open_L()));
		connect(w, SIGNAL(sig_pic_improve_open_M()), this, SLOT(pic_improve_open_M()));
		connect(w, SIGNAL(sig_pic_improve_open_H()), this, SLOT(pic_improve_open_H()));
		connect(w, SIGNAL(sig_pic_improve_close()), this, SLOT(pic_improve_close()));
		connect(w, SIGNAL(sig_ir_auto_focuse()), this, SLOT(on_btn_ir_auto_focuse_clicked()));
		connect(w, SIGNAL(sig_ir_osd_open()), this, SLOT(on_btn_ir_osd_open_clicked()));
		connect(w, SIGNAL(sig_ir_osd_close()), this, SLOT(on_btn_ir_osd_close_clicked()));
		connect(w, SIGNAL(sig_ir_auto_track()), this, SLOT(on_btn_ir_auto_track_clicked()));
		connect(w, SIGNAL(sig_ir_all_track()), this, SLOT(on_btn_ir_all_track_clicked()));
		connect(w, SIGNAL(sig_ir_black_target_2()), this, SLOT(on_btn_ir_black_target_clicked()));
		connect(w, SIGNAL(sig_ir_write_target_2()), this, SLOT(on_btn_ir_write_target_clicked()));
		connect(w, SIGNAL(sig_ir_temperature_compensation_open()), this, SLOT(pic_temperature_compensation_open()));
		connect(w, SIGNAL(sig_ir_temperature_compensation_close()), this, SLOT(pic_temperature_compensation_close()));
		connect(w, SIGNAL(sig_ir_focus_speed_L()), this, SLOT(pic_focus_speed_L()));
		connect(w, SIGNAL(sig_ir_focus_speed_M()), this, SLOT(pic_focus_speed_M()));
		connect(w, SIGNAL(sig_ir_focus_speed_H()), this, SLOT(pic_focus_speed_H()));
		w->setAttribute(Qt::WA_DeleteOnClose, true);
		w->show();
	}
}

void fzqjMain_user::on_btn_ir_black_target_clicked(void)
{
	QString str = QStringLiteral("红外-目标特征-暗");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_BLACK_TARGET;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_ir_write_target_clicked(void)
{
	QString str = QStringLiteral("红外-目标特征-白");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_WRITE_TARGET;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_ir_background_correct_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_BG_CORRECTION;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	ui.lb_mainvideo->setText(QStringLiteral("红外"));
	QString str = QStringLiteral("红外-背景-触发");
	ShowLineText(0, 0, str);
}


void fzqjMain_user::on_btn_white_ir_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_WHITE_HEAT;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	ui.lb_mainvideo->setText(QStringLiteral("红外"));
	QString str = QStringLiteral("红外-极性设置-白");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_btn_black_ir_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_BLACK_HEAT;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	ui.lb_mainvideo->setText(QStringLiteral("红外"));
	QString str = QStringLiteral("红外-极性设置-黑");
	ShowLineText(0, 0, str);
}


void fzqjMain_user::on_btn_ir_osd_open_clicked(void)
{
	QString str = QStringLiteral("红外-图像增强-关");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_OSD_OPEN;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_ir_osd_close_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_OSD_CLOSE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}


void fzqjMain_user::vl_osd_open(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_OSD_OPEN;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vl_osd_close(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_OSD_CLOSE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vl_display_mode_heibai(void)
{
	QString str = QStringLiteral("可见光-显示模式-夜晚");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VL_IR_OPEN;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vl_display_mode_caise(void)
{
	QString str = QStringLiteral("可见光-显示模式-白天");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VL_IR_CLOSE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

bool fzqjMain_user::is_windows_open(QString str_windows)
{
	QWindowList list = QGuiApplication::allWindows();
	bool isopen = false;
	for (int i = 0; i < list.size(); i++)//fzqjViMore
	{
		QString winstr = list.at(i)->title();
		if (list.at(i)->title() == str_windows)
		{
			isopen = true;
			break;
		}
	}
	if (isopen)
	{
		QString wTitle = str_windows;
		LPCWSTR str = (LPCWSTR)wTitle.toStdWString().c_str();
		HWND handle = FindWindow(nullptr, str);//基于windows Api 获取程序窗口的句柄
		ShowWindow(handle, SW_RESTORE);//激活窗口，参数：SW_RESTORE，以程序之前的大小显示，可以根据需要设置其他标识，如SW_MAXIMIZE
		SetForegroundWindow(handle);//激活窗口在桌面最前面
		return false;
	}
	else
	{
		return true;
	}
}

float fzqjMain_user::calculateNewFocalLength(float currentFocalLength, int currentPixelCount, int desiredPixelCount)
{
	if (currentPixelCount <= 0) {
		printf("Current pixel count must be positive.");
	}
	return currentFocalLength * static_cast<float>(desiredPixelCount) / currentPixelCount;
}


void fzqjMain_user::guideAutoFocus(void)
{
	if (isGetLeiDaYinDao==false)
	{
		return;
	}
	if (is_yindao_send ==false)
	{
		return;
	}
	if (is_guideing == false)
	{
		return;
	}
	if (gudie_dis<=0)
	{
		return;
	}
	int dersired_focus_vi = ((gudie_dis * pixe_size_vi * m_xk_configinfo.GUIDE_ADPAT_VIEW_PIXE_VI) / m_xk_configinfo.GUIDE_ADPAT_VIEW_SIZE) * 100000;
	int dersired_focus_ir = ((gudie_dis * pixe_size_ir * m_xk_configinfo.GUIDE_ADPAT_VIEW_PIXE_IR) / m_xk_configinfo.GUIDE_ADPAT_VIEW_SIZE) * 100000;

	int currentzoom_vi_ = m_pic_up_realtime_state.VIfocuesValue;
	int nums_vi = dersired_focus_vi - currentzoom_vi_;
	int currentzoom_ir_ = m_pic_up_realtime_state.IRfocuesValue;
	int nums_ir = dersired_focus_ir - currentzoom_ir_;
	/*cout << "nums_vi:" <<<< nums_vi << ",nums_ir:" << nums_ir;*/
	//printf("currentzoom_vi_:%d,nums_vi:%d,currentzoom_ir_:%d,nums_ir:%d\n", currentzoom_vi_, nums_vi, currentzoom_ir_, nums_ir);
	if (nums_vi > 1500)
	{
		/*if (m_pic_up_realtime_state.VIfocuesValue>=96000)
		{
			return;
		}*/
		on_btn_vl_v_add_pressed();
		
		av_usleep(150000);
		m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
		

	}
	else if (nums_vi < -1500)
	{
		/*if (m_pic_up_realtime_state.VIfocuesValue <= 1200)
		{
			return;
		}*/
		on_btn_vl_v_nadd_pressed();
		
		av_usleep(250000);
		m_xk_down_msg.msg_type = E_FK_VL_STOP_ZOOM;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
	}

	if (nums_ir> 1500)
	{
		/*if (m_pic_up_realtime_state.IRfocuesValue >= 1030)
		{
			return;
		}*/
		on_btn_ir_v_add_pressed();
		av_usleep(150000);
		m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
	}
	else if (nums_ir<-1500)
	{
		/*if (m_pic_up_realtime_state.IRfocuesValue <= 106)
		{
			return;
		}*/
		on_btn_ir_v_nadd_pressed();
		av_usleep(250000);
		m_xk_down_msg.msg_type = E_FK_IR_STOP_ZOOM;
		sendMsg2Pic();
		m_xk_down_msg.msg_type = E_FK_BUTT;
	}
}

void fzqjMain_user::on_btn_vl_more_clicked(void)
{
	bool Is_Windows_Open = is_windows_open("fzqjViMore");
	QString str = QStringLiteral("可见光--专家设置--打开");
	ShowLineText(0, 0, str);
	if (Is_Windows_Open == false)
	{
		return;
	}
	else
	{
		fzqjViMore* w = new fzqjViMore();
		connect(w, SIGNAL(sig_vi_focuse_auto()), this, SLOT(vi_focuse_auto()));
		connect(w, SIGNAL(sig_vi_focuse_manul()), this, SLOT(vi_focuse_manul()));
		connect(w, SIGNAL(sig_vi_focuse_semiAuto()), this, SLOT(vi_focuse_semiAuto()));
		connect(w, SIGNAL(sig_vi_send_clicked(QByteArray)), this, SLOT(vi_send_clicked(QByteArray)));
		connect(w, SIGNAL(sig_vi_shuiping_on()), this, SLOT(vi_shuiping_on()));
		connect(w, SIGNAL(sig_vi_shuiping_off()), this, SLOT(vi_shuiping_off()));
		connect(w, SIGNAL(sig_vi_chuizhi_on()), this, SLOT(vi_chuizhi_on()));
		connect(w, SIGNAL(sig_vi_chuizhi_off()), this, SLOT(vi_chuizhi_off()));
		connect(w, SIGNAL(sig_vi_qw_open_2(int)), this, SLOT(btn_vl_qw_open(int)));
		connect(w, SIGNAL(sig_vl_black_target()), this, SLOT(btn_vl_black_target()));
		connect(w, SIGNAL(sig_vl_write_target()), this, SLOT(btn_vl_write_target()));
		connect(w, SIGNAL(sig_vl_auto_track()), this, SLOT(vl_auto_track()));
		connect(w, SIGNAL(sig_vl_all_track()), this, SLOT(vl_all_track()));
		connect(w, SIGNAL(sig_vl_display_mode_heibai()), this, SLOT(vl_display_mode_heibai()));
		connect(w, SIGNAL(sig_vl_display_mode_caise()), this, SLOT(vl_display_mode_caise()));
		connect(w, SIGNAL(sig_vl_osd_open()), this, SLOT(vl_osd_open()));
		connect(w, SIGNAL(sig_btn_vl_osd_close()), this, SLOT(vl_osd_close()));
		w->setAttribute(Qt::WA_DeleteOnClose, true);
		w->show();
	}

}

void fzqjMain_user::vi_focuse_auto(void)
{
	QString str = QStringLiteral("可见光-调焦模式-自动");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VI_FOCUSE_AUTO;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vi_focuse_manul(void)
{
	QString str = QStringLiteral("可见光-调焦模式-手动");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VI_FOCUSE_MANUL;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vi_focuse_semiAuto(void)
{
	QString str = QStringLiteral("可见光-调焦模式-半自动");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VI_FOCUSE_SEMIAUTO;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vi_shuiping_on(void)
{
	QString str = QStringLiteral("可见光-图像翻转-水平翻转-开");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VL_RotationHorizontalOn;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vi_shuiping_off(void)
{
	QString str = QStringLiteral("可见光-图像翻转-水平翻转-关");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_Vl_RotationHorizontalOff;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vi_chuizhi_on(void)
{
	QString str = QStringLiteral("可见光-图像翻转-垂直翻转-开");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VL_RotationVerticallyOn;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vi_chuizhi_off(void)
{
	QString str = QStringLiteral("可见光-图像翻转-垂直翻转-关");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_Vl_RotationVerticallyOff;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::vi_send_clicked(QByteArray data)
{
	QString str = QStringLiteral("可见光-自定义指令-下发");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_VI_SEND_CUSTOMDATA;
	m_xk_down_msg.param_1 = data.size();
	memcpy(((byte*)&m_xk_down_msg) + 7, data, data.size());
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_guizhong_clicked(void)
{
	QString str = QStringLiteral("转台-运动-归零");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	m_xk_down_msg.msg_type = E_FK_SF_RESTORE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_shoucang_clicked(void)
{
	QString str = QStringLiteral("转台-运动-收藏");
	ShowLineText(0, 0, str);
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	int x = 0 * 1000;
	int y = -50 * 1000;
	m_xk_down_msg.msg_type = E_FK_SF_MOVE_TO;
	m_xk_down_msg.param_1 = x;
	m_xk_down_msg.param_2 = y;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::pic_improve_close(void)
{
	QString str = QStringLiteral("红外-图像增强-关");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_IMAGE_ENHANCEMENT_CLOSE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::pic_temperature_compensation_open(void)
{
	QString str = QStringLiteral("红外-温度补偿-开");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_IMAGE_TEMPERATURE_COMPENSATION_OPEN;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::pic_temperature_compensation_close(void)
{
	QString str = QStringLiteral("红外-温度补偿-关");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_IMAGE_TEMPERATURE_COMPENSATION_CLOSE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::pic_focus_speed_L(void)
{
	QString str = QStringLiteral("红外-跟焦速度-低");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_IMAGE_FOCUS_SPEED_LOW;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::pic_focus_speed_M(void)
{
	QString str = QStringLiteral("红外-跟焦速度-中");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_IMAGE_FOCUS_SPEED_MEDIUM;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::pic_focus_speed_H(void)
{
	QString str = QStringLiteral("红外-跟焦速度-高");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_IR_IMAGE_FOCUS_SPEED_HIGHT;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_fwauto_clicked(void)
{
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	m_xk_down_msg.msg_type = E_FK_SF_FWAUTO;
	m_xk_down_msg.param_1 = 0;
	m_xk_down_msg.param_2 = 10000;
	m_xk_down_msg.param_3 = 0;
	m_xk_down_msg.param_4 = 1000;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_SF_FWAUTO;
	m_xk_down_msg.param_1 = 0;
	m_xk_down_msg.param_2 = 10000;
	m_xk_down_msg.param_3 = 0;
	m_xk_down_msg.param_4 = 1000;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_fymanul_clicked(void)
{
	if (m_pic_up_realtime_state.dsp1_mode || m_pic_up_realtime_state.dsp2_mode)
	{
		qDebug() << QStringLiteral("伺服在跟踪状态！误操作");
		return;
	}
	m_xk_down_msg.msg_type = E_FK_SF_FYMANUL;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_more_clicked(void)
{
	bool Is_Windows_Open = is_windows_open("fzqjSfMore");
	QString str = QStringLiteral("转台-更多设置-打开");
	ShowLineText(0, 0, str);
	if (Is_Windows_Open == false)
	{
		return;
	}
	else
	{
		fzqjSfMore* w = new fzqjSfMore();
		connect(w, SIGNAL(sig_sf_biaojiao_X()), this, SLOT(sf_biaojiao_X()));
		connect(w, SIGNAL(sig_sf_biaojiao_Y()), this, SLOT(sf_biaojiao_Y()));
		connect(w, SIGNAL(sig_sf_shansao(int, int)), this, SLOT(sf_shansao(int, int)));
		connect(w, SIGNAL(sig_sf_zhousao()), this, SLOT(sf_zhousao()));
		connect(w, SIGNAL(sig_sf_saomiao_info(int, int, int, int)), this, SLOT(sf_saomiao_info_set(int, int, int, int)));
		connect(w, SIGNAL(sig_sf_insert(int, int, int)), this, SLOT(sf_insert(int, int, int)));
		connect(w, SIGNAL(sig_sf_toyzw(int)), this, SLOT(sf_toyzw(int)));
		connect(w, SIGNAL(sig_sf_delete(int)), this, SLOT(sf_delete(int)));
		connect(w, SIGNAL(sig_sf_biaojiao_any(int ,int )), this, SLOT(sf_biaojiao_any(int, int )));
		connect(w, SIGNAL(sig_sf_set_fy_bianjie()), this, SLOT(sf_set_fy_bianjie()));
		connect(w, SIGNAL(sig_sf_shuyin(double, double)), this, SLOT(sf_shuyin(double, double)));
		connect(w, SIGNAL(sig_sf_close()), this, SLOT(sf_close()));
		connect(w, SIGNAL(sig_sf_local_altitude()), this, SLOT(sf_info_local_altitude()));
		connect(w, SIGNAL(sig_sf_target_altitude()), this, SLOT(sf_info_target_altitude()));
		connect(w, SIGNAL(sig_target_info_all()), this, SLOT(sf_info_target_all()));
		connect(w, SIGNAL(sigUpdateBj()), this, SLOT(updateBjFwFy()));
		connect(this, &fzqjMain_user::sigUpdateSendBjFwFy, w, &fzqjSfMore::SFupdateBjFwFy);
		connect(this, &fzqjMain_user::sigSendLaserForbidPara, w, &fzqjSfMore::updateLaserForbid);
		connect(w, &fzqjSfMore::sigAcquireLaserFobid, this, &fzqjMain_user::getLaserForbidPara);
		connect(w, &fzqjSfMore::sigSetLaserForbid, this, &fzqjMain_user::setLaserForbidPara);
		connect(w, &fzqjSfMore::sigSFCompensateSet, this, &fzqjMain_user::setSfCompensate);
		
		w->setAttribute(Qt::WA_DeleteOnClose, true);
		w->show();
	}
}

void fzqjMain_user::sf_biaojiao_X(void)
{
	QString str = QStringLiteral("转台-校准-方位0位校准");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_SF_BIAOJIAO_X;
	m_xk_down_msg.param_1 = 2;//2
	m_xk_down_msg.param_2 = 0;
	m_xk_down_msg.param_3 = 0;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::sf_biaojiao_Y(void)
{
	QString str = QStringLiteral("转台-校准-俯仰0位校准");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_SF_BIAOJIAO_Y;
	m_xk_down_msg.param_1 = 3;//3
	m_xk_down_msg.param_2 = 0;
	m_xk_down_msg.param_3 = 0;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::sf_shansao(int fwCenter, int fwNum)
{
	QString str = QStringLiteral("转台-运动-扇扫");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_SF_FWAUTO;
	m_xk_down_msg.param_1 = fwCenter;
	m_xk_down_msg.param_2 = fwNum;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::sf_zhousao(void)
{
	QString str = QStringLiteral("转台-运动-周扫");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_SF_ZHOUSAO;//E_FK_SF_ZHOUSAO
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::sf_saomiao_info_set(int v, int fytop, int fyL, int fybujin)
{
	m_xk_down_msg.msg_type = E_FK_SF_SAOMIAO_INFO;
	m_xk_down_msg.param_1 = v;
	m_xk_down_msg.param_2 = fytop;
	m_xk_down_msg.param_3 = fyL;
	m_xk_down_msg.param_4 = fybujin;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::sf_insert(int num, int fw, int fy)
{
	m_xk_down_msg.msg_type = E_FK_SF_YZW_INSERT;
	m_xk_down_msg.param_1 = num;
	m_xk_down_msg.param_2 = fw;
	m_xk_down_msg.param_3 = fy;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_insert_clicked(void)
{
	QString str = QStringLiteral("转台-设置预置位：%1").arg(ui.cbx_sf_yzw_num->currentText());
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_SF_YZW_INSERT;
	m_xk_down_msg.param_1 = ui.cbx_sf_yzw_num->currentIndex() + 1;
	m_xk_down_msg.param_2 = m_pic_up_realtime_state.fw / 10;
	m_xk_down_msg.param_3 = m_pic_up_realtime_state.fy / 10;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::sf_toyzw(int num)
{
	m_xk_down_msg.msg_type = E_FK_SF_YZW_TO;
	m_xk_down_msg.param_1 = num;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::on_btn_sf_toyzw_clicked(void)
{
	QString str = QStringLiteral("转台-运动-跳转到预置位：%1").arg(ui.cbx_sf_yzw_num->currentText());
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_SF_YZW_TO;
	m_xk_down_msg.param_1 = ui.cbx_sf_yzw_num->currentIndex() + 1;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;

}

void fzqjMain_user::on_cbx_sf_yzw_num_editTextChanged(const QString&)
{
	if (b_is_sf_cbx_init && ui.cbx_sf_yzw_num->currentIndex() >= 0)
	{
		if (m_sf_yzw_list[ui.cbx_sf_yzw_num->currentIndex()] != ui.cbx_sf_yzw_num->currentText())
		{
			int index = ui.cbx_sf_yzw_num->currentIndex();

			QString key = "SF_";
			key.append(QString::number(ui.cbx_sf_yzw_num->currentIndex() + 1));
			m_configManager->set(key.toStdString(), ui.cbx_sf_yzw_num->currentText().toStdString());
			m_configManager->print("Config.ini");

			m_sf_yzw_list[ui.cbx_sf_yzw_num->currentIndex()] = ui.cbx_sf_yzw_num->currentText();

			InitSFyzw();

			ui.cbx_sf_yzw_num->setCurrentIndex(index);
		}
	}
}

void fzqjMain_user::sf_delete(int num)
{
	m_xk_down_msg.msg_type = E_FK_SF_YZW_DALETE;
	m_xk_down_msg.param_1 = num;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::sf_biaojiao_any(int fw, int fy)
{
	QString str = QStringLiteral("转台-快速校准-方位俯仰校准");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_SF_BIAOJIAO_ANY;
	m_xk_down_msg.param_1 = 1;
	if(fw<0)
	{
		fw += 360000;
	}
	if (fy < 0)
	{
		fy += 360000;
	}
	m_xk_down_msg.param_2 = fw;
	m_xk_down_msg.param_3 = fy;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::sf_set_fy_bianjie(int fy_H, int fy_L)
{

	QString str = QStringLiteral("转台-俯仰上下限位-设置");
	ShowLineText(0, 0, str);
	m_xk_down_msg.msg_type = E_FK_SF_FY_BIANJIE;
	m_xk_down_msg.param_1 = fy_H;
	m_xk_down_msg.param_2 = fy_L;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
}

void fzqjMain_user::sf_info_local_altitude(void)
{

	QString str = QStringLiteral("转台-本机高度-转换");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::sf_info_target_altitude(void)
{
	QString str = QStringLiteral("转台-目标高度-转换");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::sf_info_target_all(void)
{
	QString str = QStringLiteral("转台-目标信息-计算");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_toolButton_VI_ON_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_OPEN;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("系统控制-电视上下电-开");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_toolButton_VI_OFF_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_VL_CLOSE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("系统控制-电视上下电-关");
	ShowLineText(0, 0, str);
}


void fzqjMain_user::on_toolButton_IR_ON_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_OPEN;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("系统控制-红外上下电-开");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_toolButton_IR_OFF_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_IR_CLOSE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("系统控制-红外上下电-关");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_toolButton_savePic_VL_clicked(void)
{
	QString str = QStringLiteral("系统控制-图像存储-可见光");
	ShowLineText(0, 0, str);
	QDateTime curDateTime = QDateTime::currentDateTime();
	QString recordFileName = QStringLiteral("%1/%2%3.png").arg(m_xk_configinfo.PIC_SAVE_Addr).arg(curDateTime.toString("yyyy-MM-dd-hh-mm-ss")).arg("_VI");

	cv::imwrite(recordFileName.toStdString(), vi_mat);

}

void fzqjMain_user::on_toolButton_savePic_IR_clicked(void)
{
	QString str = QStringLiteral("系统控制-图像存储-红外");
	ShowLineText(0, 0, str);
	QDateTime curDateTime = QDateTime::currentDateTime();
	QString recordFileName = QStringLiteral("%1/%2%3.png").arg(m_xk_configinfo.PIC_SAVE_Addr).arg(curDateTime.toString("yyyy-MM-dd-hh-mm-ss")).arg("_IR");
	cv::imwrite(recordFileName.toStdString(), ir_mat);
	//img_ir.save(recordFileName, "png", 25)
}

void fzqjMain_user::on_toolButton_laser_ON_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_LASER_RANGING_OPEN;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("系统控制-激光测距上下电-开");
	ShowLineText(0, 0, str);
}

void fzqjMain_user::on_toolButton_laser_OFF_clicked(void)
{
	m_xk_down_msg.msg_type = E_FK_LASER_RANGING_CLOSE;
	sendMsg2Pic();
	m_xk_down_msg.msg_type = E_FK_BUTT;
	QString str = QStringLiteral("系统控制-激光测距上下电-关");
	ShowLineText(0, 0, str);
}


