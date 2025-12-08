#ifndef PROTOCOL_PICXK
#define PROTOCOL_PICXK
#include <stdint.h>
#include "ConfigManager.h"

#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为1字节对齐
/// <summary>
/// 控制消息结构体-显控下发给图像板
/// </summary>
typedef struct XKDownMsg
{
	uint8_t sync_code1; //0xEB
	uint8_t sync_code2; //0x90
	uint8_t msg_type;//消息类型
	int32_t param_1;//消息参数
	int32_t param_2;
	int32_t param_3;
	int32_t param_4;
	int32_t param_5;
}XKDownMsg;

typedef struct XKDownConfig
{
	uint8_t sync_code1 = 0xEB; //0xEB
	uint8_t sync_code2 = 0x90; //0x90
	uint8_t msg_type = 0x05;//E_FK_SYS_SET_ONE_CONFIG
	int32_t key_len;
	char key[250];
	int32_t value_len;
	char value[250];
}XKDownCon;

/// <summary>
/// 控制消息类型
/// </summary>
typedef enum XKMsgType
{
	//系统0
	E_FK_SYS_SELFCHECK = 0x00,//自检

	E_FK_OPEN_TARGET_CHECK = 0x01,//目标检测开启
	E_FK_CLOSE_TARGET_CHECK = 0x02,//目标检测关闭
	E_FK_SWITCH_VL = 0x03, //切换到可见光
	E_FK_SWITCH_IR = 0x04, //切换到红外
	//E_FK_SWITCH_RONGHE_OPEN = 0x05,//打开融合开关
	//E_FK_SWITCH_RONGHE_CLOSE = 0x06,//关闭融合开关
	E_FK_SYS_SET_ONE_CONFIG = 0x05,//设置一条配置参数，1：key 2：value
	E_FK_SYS_CONFIG_INFO = 0x06,//查询下位机配置参数
	E_FK_OPEN_TARGET_DISTINGUISH = 0x07,//目标识别开启
	E_FK_CLOSE_TARGET_DISTINGUISH = 0x08,//目标识别关闭
	E_FK_OPEN_GD_PROTECT = 0x09,//大光电保护协议开启
	E_FK_CLOSE_GD_PROTECT = 0x0A,//大光电保护协议关闭
	E_FK_SET_TIME = 0x0B,//设置系统时间 年月日 时 分 秒

	//可见光1-2
	E_FK_VL_BLACK_TARGET = 0x10, // 是否暗目标-是
	E_FK_VL_WRITE_TARGET = 0x11, // 是否暗目标-否

	E_FK_VL_OPEN = 0x12, //可见光上电 visible light
	E_FK_VL_CLOSE = 0x13, //可见光下电 visible light

	E_FK_VL_IR_OPEN = 0x14,//可见光红外模式
	E_FK_VL_IR_CLOSE = 0x15,//可见光非红外模式

	E_FK_VL_DEHAZE_OPEN = 0x16, //可见光去雾开启
	E_FK_VL_DEHAZE_CLOSE = 0x17, //可见光去雾关闭
	//E_FK_IR_EM_1 = 0x18, //电子变倍1x ELECTRONIC_MAGNIFICATION
	//E_FK_IR_EM_2 = 0x19, //电子变倍2x
	//E_FK_IR_EM_4 = 0x1A, //电子变倍4x

	E_FK_VI_FOCUSE_AUTO = 0x1B,//自动
	E_FK_VI_FOCUSE_MANUL = 0x1C,//手动
	E_FK_VI_FOCUSE_SEMIAUTO = 0x1D,//半自动
	E_FK_VI_SEND_CUSTOMDATA = 0x1E,//发送自定义指令

	//E_FK_LUMA_INCREASES = 0x1F, //手动调节模式下 增加亮度（光圈大）
	E_FK_VL_LUMA_SET_LEVEL = 0x20, //手动设置亮度等级

	E_FK_VL_CONTRAST_INCREASES = 0x21, //手动调节模式下 对比度增加
	E_FK_VL_CONTRAST_DECREASES = 0x22, //手动调节模式下 对比度减弱

	E_FK_VL_OSD_CLOSE = 0x23, //十字丝-关
	E_FK_VL_OSD_OPEN = 0x24, //十字丝-开

	E_FK_VL_STOP_ZOOM = 0x25, //自定义停止变倍
	E_FK_AUTO_FOCUSING = 0x26, //自动调焦
	E_FK_VL_ZOOM_INCREASES = 0x27, //连续变倍（可见光/红外）放大
	E_FK_VL_ZOOM_DECREASES = 0x28, //连续变倍（可见光/红外）缩小 这里可能是光学变倍
	E_FK_VL_FOCUSING_INCREASES = 0x29, //手动调焦+ （红外/可见光）远处调焦
	E_FK_VL_FOCUSING_DECREASES = 0x2A, //手动调焦- （红外/可见光）近处调焦

	E_FK_VL_RotationHorizontalOn = 0x2B,//水平翻转开
	E_FK_Vl_RotationHorizontalOff = 0x2C,//水平翻转关
	E_FK_VL_RotationVerticallyOn = 0x2D,//垂直翻转开
	E_FK_Vl_RotationVerticallyOff = 0x2E,//垂直翻转关

	E_FK_VL_PARAMETER_SAVE = 0x2F,//可见光参数保存


	//红外34
	E_FK_IR_ZOOM_INCREASES = 0x30, //连续变倍（可见光/红外）放大
	E_FK_IR_ZOOM_DECREASES = 0x31, //连续变倍（可见光/红外）缩小 这里可能是光学变倍
	E_FK_IR_FOCUSING_INCREASES = 0x32, //手动调焦+ （红外/可见光）远处调焦
	E_FK_IR_FOCUSING_DECREASES = 0x33, //手动调焦- （红外/可见光）近处调焦

	E_FK_IR_OPEN = 0x34, //红外上电
	E_FK_IR_CLOSE = 0x35, //红外下电 挡板处于关闭状态 

	E_FK_IR_BG_CORRECTION = 0x36, //红外以均匀为背景进行校正

	//E_FK_IR_IT_INCREASES = 0x37, //积分时间增大
	//E_FK_IR_IT_DECREASES = 0x38, //积分时间减小

	E_FK_IR_MANUL_CORRECTION = 0x39,//红外手动校正（快门校正）

	//E_FK_IR_DISS_SUN_OPEN = 0x3A,//抗阳光-开
	//E_FK_IR_DISS_SUN_CLOSE = 0x3B,//抗阳光-关
	E_FK_IR_SEND_CUSTOMDATA = 0x3C,//红外自定义指令

	E_FK_IR_WHITE_HEAT = 0x3D,//白热
	E_FK_IR_BLACK_HEAT = 0x3E,//黑热
	//E_FK_IR_MIRROR = 0x3F,//红外镜像

	E_FK_IR_UNIFORMITY_CORRECTION = 0x40,//红外靶面均匀性校正
	//E_FK_IR_IMAGE_ENHANCEMENT_INC = 0x41,	//红外图像增强+
	//E_FK_IR_IMAGE_ENHANCEMENT_DEC = 0x42,	//红外图像增强-
	E_FK_IR_IMAGE_ENHANCEMENT_CLOSE = 0x43,	//红外图像增强停止
	E_FK_IR_IMAGE_ENHANCEMENT_1 = 0x44, //图像增强 1档
	E_FK_IR_IMAGE_ENHANCEMENT_2 = 0x45, //图像增强 2档
	E_FK_IR_IMAGE_ENHANCEMENT_3 = 0x46, //图像增强 3档




	E_FK_IR_STOP_ZOOM = 0x47, //自定义停止变倍

	E_FK_IR_OSD_CLOSE = 0x4B, //十字丝-关
	E_FK_IR_OSD_OPEN = 0x4C, //十字丝-开


	E_FK_IR_BLACK_TARGET = 0x4D, //是否暗目标-是
	E_FK_IR_WRITE_TARGET = 0x4E, //是否暗目标-否

	E_FK_IR_PARAMETER_SAVE = 0x4F,//红外参数保存

	E_FK_IR_IMAGE_TEMPERATURE_COMPENSATION_OPEN = 0x37,//打开温度补偿
	E_FK_IR_IMAGE_TEMPERATURE_COMPENSATION_CLOSE = 0x38,//关闭温度补偿

	E_FK_IR_IMAGE_FOCUS_SPEED_LOW = 0x3A,//聚焦速度低档 20
	E_FK_IR_IMAGE_FOCUS_SPEED_MEDIUM = 0x3B,//聚焦速度低档 70
	E_FK_IR_IMAGE_FOCUS_SPEED_HIGHT = 0x3F,//聚焦速度低档 100


	//伺服56

	E_FK_SF_OPEN = 0x50, //上电 visible light
	E_FK_SF_CLOSE = 0x51, //下电 visible light

	E_FK_SF_STOP = 0x56,//刹车 伺服立即停止当前动作
	E_FK_SF_SHOUC = 0x57, //收藏 镜头向上收起
	E_FK_SF_LOCK = 0x58, //锁定  即保持伺服和机头的相对角度不变
	E_FK_SF_MOVE = 0x59, //手动加矩 使伺服转动 速度环控制
	E_FK_SF_MOVE_TO = 0x5A,//数引 伺服转到指定的方位俯仰角度
	//E_FK_GYRO_AZIMUTH_PLUS = 0x5B, //陀螺方位修正+
	//E_FK_GYRO_AZIMUTH_MINUS = 0x5C, //陀螺方位修正-
	//E_FK_GYRO_ELEVATION_PLUS = 0x5D, //陀螺俯仰修正+
	//E_FK_GYRO_ELEVATION_MINUS = 0x5F, //陀螺俯仰修正-
	E_FK_SF_BIAOJIAO_ANY = 0x5B,//伺服方位俯仰标校
	E_FK_SF_FY_BIANJIE = 0x5C,//伺服俯仰边界设置

	E_FK_SF_RESTORE = 0x60,//归中 伺服归零  
	E_FK_SF_FWAUTO = 0x61,	//方位扫描
	E_FK_SF_FYMANUL = 0x62,//俯仰手动
	E_FK_SF_NORMAL = 0x63,			//伺服正常工作
	E_FK_SF_LOW_POWER = 0x64,			//伺服低功耗运行

	E_FK_SF_BIAOJIAO_X = 0x65,//伺服方位标校0位
	E_FK_SF_BIAOJIAO_Y = 0x66,//伺服俯仰标校0位
	E_FK_GYRO_UPPLEFT = 0x67,//伺服左上移动
	E_FK_GYRO_UPPRIGHT = 0x68,//伺服右上移动
	E_FK_GYRO_LOWERLEFT = 0x69,//伺服左下移动
	E_FK_GYRO_LOWERRIGHT = 0x6A,//伺服右下移动

	E_FK_SF_SAOMIAO_INFO = 0x6B,//伺服扇扫周扫参数设置，扫描速度，俯仰边界，步进值
	E_FK_SF_ZHOUSAO = 0x6C,//周扫

	E_FK_SF_YZW_INSERT = 0x6D,//预置位新增、修改
	E_FK_SF_YZW_TO = 0x6E,//转到
	E_FK_SF_YZW_DALETE = 0x6F,//删除
	

	//测距机7
	E_FK_LASER_RANGING_CLOSE = 0x70,//激光测距下电
	E_FK_LASER_RANGING_OPEN = 0x71, //激光测距下电
	E_FK_LASER_RANGING_ONE = 0x72,//单次测距
	E_FK_LASER_RANGING_MANY = 0x73, //连续测距
	//激光雷达9a
	//视频图像bc
	E_FK_OPEN_PIP = 0xB0, //以当前显示画面为大画面，在画中画模式下切换可见光、红外时以选择的传感器为大画面输出，控制指令仅对该传感器有效
	E_FK_CLOSE_PIP = 0xB1,//关闭画中画
	E_FK_GRAB_PIC = 0xB2, //抓图/单拍
	E_FK_GRAB_PICS_START = 0xB3, //开始连拍 按4s周期进行连续拍照
	E_FK_GRAB_PICS_STOP = 0xB4, //停止拍照
	E_FK_SWITCH_IR_VL = 0xB5, //切换到红外可见双路输出
	E_FK_STOP_RECORD = 0xB6, // 停止录像
	E_FK_START_RECORD = 0xB7, //开始录像
	//算法模块de

	E_FK_SWITCH_TRACK_RECT_MID = 0xD0, //切换中跟踪框
	E_FK_SWITCH_TRACK_RECT_BIG = 0xD1, //切换大跟踪框
	E_FK_SWITCH_TRACK_RECT_SMALL = 0xD2, //切换小跟踪框
	E_FK_SWITCH_TRACK_RECT_AUTO = 0xD3, //切换自适应跟踪框
	E_FK_AUTO_TRACK_ONE_TARGET = 0xD4, //自动跟踪/跟踪点切换
	E_FK_EXIT_TRACK = 0xD5, //退出跟踪
	E_FK_AUTO_TRACK_ONE_TARGET_SQUAL = 0xD6,	//与0XB1配合使用，传入右键方框大小
	E_FK_SYS_IMAGE_IMPROVE_OPEN = 0xD7,//打开图像增强
	E_FK_SYS_IMAGE_IMPROVE_CLOSE = 0xD8,//关闭图像增强
	E_FK_SYS_IMAGE_IMPROVE_TYPE = 0xD9,//红外相机增强参数

	E_FK_AUTO_TRACK_ALL_VL = 0xE0, //可见光全帧跟踪
	E_FK_AUTO_TRACK_ALL_IR = 0xE1, //红外全帧跟踪
	E_FK_AUTO_TRACK_ONE_VL = 0xE2, //可见光局部跟踪
	E_FK_AUTO_TRACK_ONE_IR = 0xE3, //红外局部跟踪
	E_FK_AUTO_TRACK_AUTO_VL = 0xE4, //可见光自动跟踪
	E_FK_AUTO_TRACK_AUTO_IR = 0xE5, //红外自动跟踪
	E_FK_AUTO_DETECT_ONE_VL = 0xE6, //可见光局部检测
	E_FK_AUTO_DETECT_ONE_IR = 0xE7, //红外局部检测
	E_FK_REBOOT = 0xE8, //看门狗，重启下位机
	E_FK_SF_COMPALATE = 0xE9,//伺服零漂设置

	E_FK_BUTT = 0xFF			//无意义
}XKMsgType;


/// <summary>
/// 接收消息结构体-包含FK1与FK2
/// </summary>
typedef enum PICUpMessageTypeEnum
{
	FKUP_REALTIME_STATE_E = 0x0,//实时状态
	FKUP_SELFCHECK_STATE_E = 0x1,//自检信息
	FKUP_CONFIG_INFO_E = 0x2,//配置参数
	FKUP_DWDX_INFO_E = 0x3,//北斗信息

	FKUP_MAX_STATE_E = 0xff,
}PICUpMsgTypeE;

/// <summary>
/// 接收PIC-实时状态
/// </summary>
typedef struct PICUpRealTimeStateMsgStruct //25hz
{
	uint16_t sync_code;//0xEB90
	uint16_t type;//FKUP_REALTIME_STATE_E
	//伺服
	int32_t fw;//0.001度
	int32_t fy;//0.001度
	uint8_t state;//伺服控制组件 D0 方位编码器； D1 俯仰编码器； D2 方位驱动器； D3 俯仰驱动器； D4 伺服控制板； D5 方位陀螺仪； D6 俯仰陀螺仪
	uint8_t mode;//伺服状态1进行0无效(默认) D0 俯仰扇形扫描； D1 方位扇形扫描 ；D2随动； D3 跟踪； D4 收藏；D5 归零位； D6 伺服停止； D7 方位圆周扫描 
	//相机
	uint16_t VIzoomValue;
	uint32_t VIfocuesValue;
	uint16_t VIshichang_X;//0.01
	uint16_t VIshichang_Y;//0.01
	uint16_t IRzoomValue;
	uint32_t IRfocuesValue;
	uint16_t IRshichang_X;//0.01
	uint16_t IRshichang_Y;//0.01
	//测距
	uint16_t fake_distance;//伪距值 1m
	uint16_t error_distance;//测距机异常值
	//目标
	uint8_t dsp1_mode;
	int16_t dsp1_target_x;//x坐标
	int16_t dsp1_target_y;//y坐标 
	int16_t dsp1_target_fw;//水平脱靶量 0.001
	int16_t dsp1_target_fy;//垂直脱靶量 0.001
	int16_t dsp1_target_size;//目标面积
	int16_t dsp1_target_num;//目标数量
	int32_t dsp1_target_jd;//目标经度
	int32_t dsp1_target_wd;//目标纬度
	int32_t dsp1_target_gd;//目标高度
	uint8_t dsp2_mode;
	int16_t dsp2_target_x;//x坐标
	int16_t dsp2_target_y;//y坐标
	int16_t dsp2_target_fw;//水平脱靶量 0.001
	int16_t dsp2_target_fy;//垂直脱靶量 0.001
	int16_t dsp2_target_size;//目标面积
	int16_t dsp2_target_num;//目标数量
	int32_t dsp2_target_jd;//目标经度
	int32_t dsp2_target_wd;//目标纬度
	int32_t dsp2_target_gd;//目标高度

	uint8_t AI_target_type_VL;//AI目标类型
	uint8_t AI_target_type_IR;//AI目标类型
	//软件状态
	uint8_t video_mode;//视频模式 0可见光 1红外
	uint8_t ronghe_mode;//融合模式 0关闭 1开启
	uint8_t image_mode;//图像增强 0关闭 1开启
	uint8_t trace_mode;//  跟踪算法 0关闭 1开启
	uint8_t detector_mode;// 检测算法 0关闭 1开启
	uint32_t ai_vi_size;//ai可见光中心目标大小
	uint32_t ai_ir_size;//ai红外中心目标大小

}PICUpStateMsgS;

/// <summary>
/// 接收PIC-自检状态信息
/// </summary>
typedef struct PICUpSelfCheckStateStruct//30s1次
{
	uint16_t sync_code;//0xEB90
	uint16_t type;//FKUP_SELFCHECK_STATE_E
	float boardtemp1;//主板温度1
	float boardtemp2;//主板温度2
	float boardHumidity;//主板湿度
	float boardPressure;//主板压力
	float fpgaTemp;//FPGA温度
	float cur1;//加热膜1电流
	float temp1;//加热膜1温度
	float tempControl;//控制板温度
	float fanSpeed;//风扇转速
	float ecHumidity;//环控湿度
	float ecPressure;//环控压强

	int8_t ccdState;//可见光状态--接收焦距值，超时复位
	int8_t irState;//红外状态--接收焦距值，超时复位
	int8_t distanceState;//测距机状态--定时发75指令，无回复掉线
	int8_t sfState;//伺服状态--接收状态，超时复位
	int8_t detectorState;//AI检测器状态--获取
	int8_t traceState;//dsp跟踪器osd状态--获取
	int8_t beidouState;//定位设备状态--接收北斗信息，超时复位
};

/// <summary>
/// 显控配置文件信息
/// </summary>
typedef struct XKConfigInfo
{
	char XK_IP[15];//192.168.0.100
	char GD_IP[15];//192.168.0.90
	char FK_IP[15];//192.168.1.6
	char VI_RTSP_Addr[100];//rtsp://192.168.0.90:554/vl
	char IR_RTSP_Addr[100];//rtsp://192.168.0.90:555/ir

	int VI_H264_Port;//10001
	int IR_H264_Port;//10002
	int XK_Recv_GD_INFO_Port;//11000
	int XK_Send_GD_INFO_Port;//10001
	int XK_Send_FK_INFO_Port;//35498
	int FK_Send_XK_INFO_Port;//21000

	double this_jingdu;
	double this_weidu;
	double this_gaodu;

	char PIC_SAVE_Addr[200];//图片存储地址
	char VIDEO_SAVE_Addr[200];//图片存储地址
	char LOG_SAVE_Addr[200];//图片存储地址

	bool IS_WARNING_TARGET;
	uint32_t sourceID;//信源地址
	uint32_t devID; //设备编号
	int IS_GUIDE_ADAPT_VIEW; //是否自适应视场
	int GUIDE_ADPAT_VIEW_PIXE_VI;//自适应视场像素个数可见光
	int GUIDE_ADPAT_VIEW_PIXE_IR;//自适应视场像素个数红外
	int GUIDE_ADPAT_VIEW_SIZE;
	float laser_forbid_fw_start;
	float laser_forbid_fw_stop;
	float laser_forbid_fy_start;
	float laser_forbid_fy_stop;
};

/// <summary>
/// 下位机配置文件信息
/// </summary>
typedef struct GDConfigInfo
{
	uint16_t sync_code;//0xEB90
	uint16_t type;//

	char XK_IP[15];//192.168.0.100
	char GD_IP[15];//192.168.0.90
	char VI_RTSP_Addr[100];//rtsp://192.168.0.90:554/vl
	char IR_RTSP_Addr[100];//rtsp://192.168.0.90:555/ir

	int VI_H264_Port;//10001
	int IR_H264_Port;//10002
	int GD_Send_XK_INFO_Port;//11000
	int GD_Recv_XK_INFO_Port;//10001

	float AI_VI_ThreShold;//可见光检测阈值 0.1
	float AI_IR_ThreShold;//红外检测阈值 0.1

	char VI_OSD_NAME[100];//大光电 可见光 V1
	char IR_OSD_NAME[100];//大光电 红外 V1
};

typedef struct RecvBeiDouInfo
{
	uint16_t sync_code = 0xEB90;//0xEB90
	uint16_t type = (uint16_t)FKUP_DWDX_INFO_E;//FKUP_REALTIME_STATE_E

	int GPSWeek; //自 1980 - 1 - 6 至当前的星期数（接收机时间） wwww 1451
	float GPSTime;// 星期内的秒数（接收机时间） ssssss.sss 368123.300
	float Heading;//偏航角（0~359.99）（后天线指向前天线） hhh.hh 90.01
	float Pitch;// 俯仰角（ - 90~90） + / -pp.pp 0.12
	float Track;// 地速相对真北方向的夹角（0~359.99） + / -ttt.tt 90.11
	float Latitude;// 纬度(-90～90) + / -ll.lllllll 34.1966004
	float Longitude;// 经度(-180～180) + / -lll.lllllll 108.8511121
	float Altitude;// 高度，单位（米） + / -aaaaa.aa 394.98
	float Ve;// 东向速度，单位（米 / 秒） + / -eee.eee - 0.157
	float Vn;// 北向速度，单位（米 / 秒） + / -nnn.nnn 0.019
	float Vu;// 天向速度，单位（米 / 秒） + / -uuu.uuu - 0.345
}RecvBeiDouInfo;

struct HEALTH_CTL_MSG
{
	uint8_t AReboot;
	uint8_t AKill;
	uint8_t AutoReboot;
};
#pragma pack(pop)

void init_XKConfigInfo(ConfigManager* config, XKConfigInfo* info);
void init_GDConfigInfo(ConfigManager* config, GDConfigInfo* info);

void init_pic_up_realtime_msg(PICUpRealTimeStateMsgStruct* msg);

void init_pic_up_selfcheck_msg(PICUpSelfCheckStateStruct* msg);

void init_xk_down_msg(XKDownMsg* msg);

#endif
