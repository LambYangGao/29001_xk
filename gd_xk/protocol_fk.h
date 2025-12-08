#ifndef PROTOCOL_FK
#define PROTOCOL_FK
#include <stdint.h>

#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为1字节对齐
/// <summary>
/// 心跳消息结构体-显控上报给防控
/// </summary>
typedef struct XKUpHeartMsg
{
	//帧头
	uint64_t fkhead; //0xAAAAAAAABBBBBBBB
	uint8_t version; //0x01
	uint16_t MLen;//0x0
	uint64_t TS;//时间戳 0
	uint16_t jobID;//任务编号 0
	uint8_t devID[20];//设备编号 0
	uint32_t sourceID;//信源地址 0
	uint32_t destinationID;//目的地址 0
	uint32_t reserve1;//保留字段 0

	uint16_t flag;//心跳标志 0x0200
}XKUpHeartM;

/// <summary>
/// 设备状态消息结构体-显控上报给防控
/// </summary>
typedef struct XKUpDevStateMsg
{
	//帧头
	uint64_t fkhead; //0xAAAAAAAABBBBBBBB
	uint8_t version; //0x01
	uint16_t MLen;//0x0
	uint64_t TS;//时间戳 0
	uint16_t jobID;//任务编号 0
	uint8_t devID[20];//设备编号 0
	uint32_t sourceID;//信源地址 0
	uint32_t destinationID;//目的地址 0
	uint32_t reserve10;//保留字段 0   53

	uint16_t flag;//报文标志 0x0201
	uint8_t locationFlag;//位置标志 0:WGS-84；	1:CGCS2000;	2:BD09;	3:其它
	int32_t Lon;//经度 [-180000000,180000000] 0.000001°
	int32_t Lat;//纬度 [-90000000,90000000] 0.000001°
	int32_t Alt;//海拔高度 [-20000,100000000] 0.01m
	uint64_t devstate; //设备状态
	uint16_t ztAz;//转台方位角度	[0,3600] 0.1°
	uint16_t ztPc;//转台俯仰角度   [-900,900] 0.1°
	uint16_t view_Zoom;//当前焦距	
	uint8_t trackState;//0：搜索；	1：跟踪；	2：手动跟踪。
	uint16_t targetAz;//目标方位 [0,3600] 0.1°基准方位为地理正北，顺时针方向递增
	uint16_t targetPc;//目标俯仰 [-900,900] 0.1°
	uint32_t targetDis;//目标距离 1米
	uint8_t targetType;//目标属性 
	uint16_t pixel_nums;//像素个数
	uint8_t current_camera;//当前摄像头
	uint8_t reserve;//
}XKUpDevState;

/// <summary>
/// 日志消息结构体-显控上报给防控
/// </summary>
typedef struct XKUpLogMsg
{
	//帧头
	uint64_t fkhead; //0xAAAAAAAABBBBBBBB
	uint8_t version; //0x01
	uint16_t MLen;//0x0
	uint64_t TS;//时间戳 0
	uint16_t jobID;//任务编号 0
	uint8_t devID[20];//设备编号 0
	uint32_t sourceID;//信源地址 0
	uint32_t destinationID;//目的地址 0
	uint32_t reserve10;//保留字段 0    53

	uint16_t flag;//日志标志 0x0202
	uint64_t optTime;//操作时间	UTC时间
	char OptCnt[512];//操作内容 
	uint64_t reserve1;//保留字段
}XKUpLogM;

//---------------------------------------------------------------------
/// <summary>
/// 接收消息结构体
/// </summary>
typedef enum FKDownMessageTypeEnum
{
	FKDOWN_TARGET_GUIDE = 0x0210,//防控引导
	FKDOWN_POWER_CONTROL = 0x0211,//上下电
	FKDOWN_ZT_CONTROL = 0x0212,//转台控制
	FKDOWN_VL_CONTROL = 0x0213,//可见光控制
	FKDOWN_IR_CONTROL = 0x0214,//红外控制	
	FKDOWN_GD_PROTECT=0x021c,//大光电保护

	FKUP_MAX_STATE_EE = 0xffff,
}FKDownMessageTypeE;

/// <summary>
/// 引导消息结构体-防控下发给显控
/// </summary>
typedef struct FKDownGuideMsg
{
	//帧头
	uint64_t fkhead; //0xAAAAAAAABBBBBBBB
	uint8_t version; //0x01
	uint16_t MLen;//0x0
	uint64_t TS;//时间戳 0
	uint16_t jobID;//任务编号 0
	uint8_t devID[20];//设备编号 0
	uint32_t sourceID;//信源地址 0
	uint32_t destinationID;//目的地址 0
	uint32_t reserve10;//保留字段 0

	uint16_t flag;//日志 0x0210

	uint16_t targetID;//目标批号
	uint8_t targetInfoSource;//目标信息来源 0x01：雷达；	0x02：融合；		0x03：无线电测；		0x04：上级指挥。
	uint8_t locationFlag;//位置标识 0:WGS-84；	1:CGCS2000;	2:BD09;	3:其它
	int32_t Lon;//经度 [-180000000,180000000] 0.000001°
	int32_t Lat;//纬度 [-90000000,90000000] 0.000001°
	int32_t Alt;//海拔高度 [-20000,100000000] 0.01m
	uint16_t targetSpeed;//速度 0.1米/秒
	uint16_t headDirection;//航向 [0,3600] 0.1°基准方位为地理正北，顺时针方向递增
	uint8_t targetTypheadDirectione;//目标属性 
	uint32_t reserve1;//保留字段
}FKDownGuideM;

/// <summary>
/// 上下电消息结构体-防控下发给显控
/// </summary>
typedef struct FKDownPowerControlMsg
{
	//帧头
	uint64_t fkhead; //0xAAAAAAAABBBBBBBB
	uint8_t version; //0x01
	uint16_t MLen;//0x0
	uint64_t TS;//时间戳 0
	uint16_t jobID;//任务编号 0
	uint8_t devID[20];//设备编号 0
	uint32_t sourceID;//信源地址 0
	uint32_t destinationID;//目的地址 0
	uint32_t reserve10;//保留字段 0

	uint16_t flag;//标志 0x0211

	uint8_t ztPower;//0：上电；	1：下电。
	uint8_t lanserPower;//0：上电；	1：下电。
	uint8_t vlPower;//0：上电；	1：下电。
	uint8_t irPower;//0：上电；	1：下电。
	uint32_t reserve1;//保留字段
}FKDownPowerControlM;

/// <summary>
/// 转台消息结构体-防控下发给显控
/// </summary>
typedef struct FKDownZTControlMsg
{
	//帧头
	uint64_t fkhead; //0xAAAAAAAABBBBBBBB
	uint8_t version; //0x01
	uint16_t MLen;//0x0
	uint64_t TS;//时间戳 0
	uint16_t jobID;//任务编号 0
	uint8_t devID[20];//设备编号 0
	uint32_t sourceID;//信源地址 0
	uint32_t destinationID;//目的地址 0
	uint32_t reserve10;//保留字段 0

	uint16_t flag;//标志 0x0212

	uint8_t CentrlContrl;//0：开始控制；	1：解除控制
	uint8_t ContrlTurnl;//1：向左运动；	2：向右运动；		3：向上运动；		4：向下运动；		0：停止运动。
}FKDownZTControlM;

/// <summary>
/// 可见光消息结构体-防控下发给显控
/// </summary>
typedef struct FKDownVLControlMsg
{
	//帧头
	uint64_t fkhead; //0xAAAAAAAABBBBBBBB
	uint8_t version; //0x01
	uint16_t MLen;//0x0
	uint64_t TS;//时间戳 0
	uint16_t jobID;//任务编号 0
	uint8_t devID[20];//设备编号 0
	uint32_t sourceID;//信源地址 0
	uint32_t destinationID;//目的地址 0
	uint32_t reserve10;//保留字段 0

	uint16_t flag;//标志 0x0213

	uint8_t CentrlContrl;//0：开始控制；	1：解除控制
	uint8_t ContrlTurnl;//1：长焦2：短焦；	3：聚焦 + ；4：聚焦 - ；5：透雾关；6：透雾开；7：自动聚焦；0：停止运动。
}FKDownVLControlM;

/// <summary>
/// 红外消息结构体-防控下发给显控
/// </summary>
typedef struct FKDownIRControlMsg
{
	//帧头
	uint64_t fkhead; //0xAAAAAAAABBBBBBBB
	uint8_t version; //0x01
	uint16_t MLen;//0x0
	uint64_t TS;//时间戳 0
	uint16_t jobID;//任务编号 0
	uint8_t devID[20];//设备编号 0
	uint32_t sourceID;//信源地址 0
	uint32_t destinationID;//目的地址 0
	uint32_t reserve10;//保留字段 0

	uint16_t flag;//标志 0x0214

	uint8_t CentrlContrl;//0：开始控制；	1：解除控制
	uint8_t ContrlTurnl;//1：长焦2：短焦；	3：聚焦 + ；4：聚焦 - ；5：内部校正5；7：自动聚焦；0：停止运动。
}FKDownIRControlM;

typedef struct FKDownGDprotectMsg
{
	uint64_t	fhd;//帧头标识
	uint8_t		ver;//协议版本
	uint16_t	mLen;//帧长
	uint64_t	ts;//时间戳
	uint16_t	bid;//任务编号
	uint8_t		did;//设备编号
	uint32_t	sourceId;//信源地址
	uint32_t	destId;//目的地址
	uint32_t	reserve;//保留字段

	uint16_t fd;//帧标识
	uint16_t secure;//开启\关闭
	uint32_t reserve2;//保留字段
}FKDownGDprotectM;

/// <summary>
/// 无人机类型结构体
/// </summary>
typedef enum FKTargetTypeEnum
{
	FK_TARGET_UNKNOWN = 0x00,//不明
	FK_TARGET_ZHISHENG = 0x01,//直升机
	FK_TARGET_GUDINGYI_WRJ = 0x02,//固定翼无人机
	FK_TARGET_XUANYI_WRJ = 0x03,//旋翼无人机
	FK_TARGET_MINHANG = 0x04,//民航
	FK_TARGET_CHE = 0x05,//车
	FK_TARGET_NIAO = 0x06,//鸟
	FK_TARGET_KONGPIAOQIU = 0x07,//空飘球
	FK_TARGET_DAXING_WRJ = 0x08,//大型无人机
	FK_TARGET_KONGPIAOWU = 0x09,//空飘物

	FKUP_MAX_STATE_EEE = 0xff,
}FKTargetTypeE;

#pragma pack(pop)

void init_xk_up_heart_msg(XKUpHeartMsg* msg);

void init_xk_up_devState_msg(XKUpDevStateMsg* msg);

void init_xk_up_log_msg(XKUpLogMsg* msg);

#endif
