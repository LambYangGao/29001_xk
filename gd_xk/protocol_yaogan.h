#ifndef PROTOCOL_YAOGAN
#define PROTOCOL_YAOGAN
#define POSPROTECT 1000//移动1000以内，算误触

#include <QObject>
#include "threadobject.h"
#include<Windows.h>
#include <joystickapi.h>
#include <QMetaType>
//#include<MMSystem.h>
//#include <WinUser.h>
//#pragma comment(lib, "Winmm.lib")

/// <summary>
/// 摇杆方位移动
/// </summary>
typedef struct JoyPosInfoMsg
{
	uint16_t Xpos;//俯仰 0-16383 8191 和距离无关，只和油门有关，可设置一个误触保护阈值
	uint16_t Ypos;//方位 0-16383 8191
	uint16_t Zpos;//油门 0-255 上快下慢
	bool isMove;
}JoyPosInfoM;

/// <summary>
/// 摇杆按钮操作
/// </summary>
typedef struct JoyBtnInfoMsg
{
	uint16_t btnNum;//按钮编号 0-15
	bool isbtnPress;//1 按下 0 抬起
}JoyBtnInfoM;

/// <summary>
/// 摇杆按钮编号
/// </summary>
typedef enum JoyBtnNumEnum
{
	YAOGAN_0_ = 0,//0x01,//跟踪/取消跟踪
	YAOGAN_1_ = 1,//0x02,//视场大
	YAOGAN_2_ = 2,//0x04,//视场小
	YAOGAN_3_ = 3,//0x08,
	YAOGAN_4_ = 4,//0x10,//调焦+
	YAOGAN_5_ = 5,//0x20,//调焦减
	YAOGAN_6_ = 6,//0x40,//切换相机
	YAOGAN_7_ = 7,//0x80,
	YAOGAN_8_ = 8,//0x0100,
	YAOGAN_9_ = 9,//0x0200,
	YAOGAN_10_ = 10,//0x0400,
	YAOGAN_11_ = 11,//0x0800,
	YAOGAN_12_ = 12,//0x1000,
	YAOGAN_13_ = 13,//0x2000,
	YAOGAN_14_ = 14,//0x4000,
	YAOGAN_15_ = 15,//0x8000,

}JoyBtnNumE;

class protocol_yaogan : public QThread
{
    Q_OBJECT
public:
    explicit protocol_yaogan(QObject *parent = nullptr);
    ~protocol_yaogan(void);
    virtual void run(void) override;
    void test_getJoyInfo(void);
	JoyPosInfoMsg joyPosInfo;
	JoyBtnInfoMsg joyBtnInfo;
	int lastBtnNum = 0;//上次按钮信息，多个按钮的和，0-1111 1111 1111 1111
	bool b_yaogan_state = false;
	int lastPovNum = 65535;
signals:
    void sig_PosEvent(JoyPosInfoMsg info);//摇杆位移-转台移动
	void sig_BtnEvent(JoyBtnInfoMsg info);//按钮事件
	void sig_PovEvent(bool state);//方向键-激光测距（根据用户要求暂时作废）
	void sig_SateEvent(bool state);
private slots:

};

#endif // UDPSOCKET_H
