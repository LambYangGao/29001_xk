#include "protocol_yaogan.h"
#include <iostream>
using namespace std;

protocol_yaogan::protocol_yaogan(QObject* parent)
	: QThread(parent)
{
	qRegisterMetaType<JoyPosInfoMsg>("JoyPosInfoMsg");
	qRegisterMetaType<JoyBtnInfoMsg>("JoyBtnInfoMsg");
}

protocol_yaogan::~protocol_yaogan(void)
{

}

void protocol_yaogan::run(void)
{
	//test_getJoyInfo();
	LPJOYINFOEX info = new JOYINFOEX;//创建当前摇杆信息对象
	//需要首先设定结构体中成员dwSize和dwFlags。
	info->dwSize = 13 * 4;//最小值，否则会报错
	info->dwZpos = 0;
	info->dwFlags = JOY_RETURNBUTTONS | JOY_RETURNRAWDATA;//唯一找到的有用的标识符

	while (true)
	{
		uint id = JOYSTICKID1;
		//不断读取摇杆的当前状态，且返回
		JOYCAPSA jc;//创建结构体变量，用来获取摇杆支持的功能
		joyGetDevCapsA(id, &jc, sizeof JOYCAPSA);
		if (jc.wPid != 45322)
		{
			id = JOYSTICKID2;
		}
		int res = joyGetPosEx(id, info);
		if (res != 0)
		{
			if (b_yaogan_state == true)
			{
				b_yaogan_state = false;
				emit sig_SateEvent(b_yaogan_state);
			}
			Sleep(1000);//程序暂停1秒
		}
		else
		{
			if (b_yaogan_state == false)
			{
				b_yaogan_state = true;
				emit sig_SateEvent(b_yaogan_state);
			}
			//摇杆移动
			bool xdo = abs((int)info->dwXpos - 8191) > POSPROTECT;
			bool ydo = abs((int)info->dwYpos - 8191) > POSPROTECT;
			if (xdo || ydo)
			{
				joyPosInfo.isMove = true;
				joyPosInfo.Xpos = xdo ? info->dwXpos : 8191;
				joyPosInfo.Ypos = ydo ? info->dwYpos : 8191;
				joyPosInfo.Zpos = info->dwZpos;
				emit sig_PosEvent(joyPosInfo);
			}
			else
			{
				if (joyPosInfo.isMove)//触发伺服停止
				{
					joyPosInfo.isMove = false;
					emit sig_PosEvent(joyPosInfo);
				}
			}
			//方向键
			if (info->dwPOV != lastPovNum)
			{
				if (info->dwPOV == 65535)
				{
					emit sig_PovEvent(false);
				}
				else
				{
					emit sig_PovEvent(true);
				}
				lastPovNum = info->dwPOV;
			}
			//按钮事件-支持多键操作
			if (lastBtnNum != 0 || info->dwButtons != 0)
			{
				bool oldstate, newstate;
				for (int i = 0; i < 16; i++)
				{
					oldstate = (lastBtnNum >> i) & 1;
					newstate = (info->dwButtons >> i) & 1;
					//少了的，触发抬起事件
					if ((oldstate) && (!newstate))
					{
						joyBtnInfo.btnNum = i;
						joyBtnInfo.isbtnPress = false;
						emit sig_BtnEvent(joyBtnInfo);
					}
					//多了的，触发按下事件
					if ((!oldstate) && (newstate))
					{
						joyBtnInfo.btnNum = i;
						joyBtnInfo.isbtnPress = true;
						emit sig_BtnEvent(joyBtnInfo);
					}
				}
				lastBtnNum = info->dwButtons;
			}

			Sleep(100);//50hz
		}

	}
}

void protocol_yaogan::test_getJoyInfo(void)
{
	JOYCAPSA jc;//创建结构体变量，用来获取摇杆支持的功能
	joyGetDevCapsA(JOYSTICKID2, &jc, sizeof JOYCAPSA);
	//输出摇杆的功能信息
	cout << "制造商标识符：" << jc.wMid << endl;
	cout << "产品商标识符：" << jc.wPid << endl;
	cout << "产品名称：" << jc.szPname << endl;
	cout << "最小X坐标：" << jc.wXmin << endl;
	cout << "最大X坐标：" << jc.wXmax << endl;
	cout << "最小Y坐标：" << jc.wYmin << endl;
	cout << "最大Y坐标：" << jc.wYmax << endl;
	cout << "最小Z坐标：" << jc.wZmin << endl;
	cout << "最大Z坐标：" << jc.wZmax << endl;
	cout << "操纵杆数量：" << jc.wNumButtons << endl;
	cout << "最小轮询频率：" << jc.wPeriodMin << endl;
	cout << "最大轮询频率：" << jc.wPeriodMax << endl;
	cout << "最小舵值：" << jc.wRmin << endl;
	cout << "最大舵值：" << jc.wRmax << endl;
	cout << "最小U坐标：" << jc.wUmin << endl;
	cout << "最大U坐标：" << jc.wUmax << endl;
	cout << "最小V坐标：" << jc.wVmin << endl;
	cout << "最大V坐标：" << jc.wVmax << endl;
	cout << "操纵杆功能：" << jc.wCaps << endl;
	cout << "最大轴数：" << jc.wMaxAxes << endl;
	cout << "当前轴数：" << jc.wNumAxes << endl;
	cout << "最大按键数：" << jc.wMaxButtons << endl;
	cout << "注册表项：" << jc.szRegKey << endl;
	cout << "驱动程序oem：" << jc.szOEMVxD << endl;
	cout << endl;

	LPJOYINFOEX info = new JOYINFOEX;//创建当前摇杆信息对象
	//需要首先设定结构体中成员dwSize和dwFlags。
	info->dwSize = 13 * 4;//最小值，否则会报错
	info->dwFlags = JOY_RETURNBUTTONS | JOY_RETURNRAWDATA;//唯一找到的有用的标识符
	while (true)
	{
		int res = joyGetPosEx(JOYSTICKID2, info);
		//不断读取摇杆的当前状态，且返回
		cout << "返回值：" << res << endl;
		cout << "size：" << info->dwSize << endl;
		cout << "flags:" << info->dwFlags << endl;
		cout << "xpos:" << info->dwXpos << endl;//摇杆x方位----0-8192-16383
		cout << "ypos:" << info->dwYpos << endl;//摇杆y方位
		cout << "zpos:" << info->dwZpos << endl;//油门
		cout << "rpos:" << info->dwRpos << endl;//右摇杆x方位-此摇杆无
		cout << "upos:" << info->dwUpos << endl;//右摇杆y方位-此摇杆无
		cout << "vpos:" << info->dwVpos << endl;
		cout << "buttons:" << info->dwButtons << endl;//32个组合按键
		cout << "buttonNumber:" << info->dwButtonNumber << endl;
		cout << "POV:" << info->dwPOV << endl;//方位按键
		cout << endl;

		//方向键
		if (info->dwPOV == JOY_POVFORWARD)//前
		{
			
			("前");
		}
		if (info->dwPOV == JOY_POVCENTERED)//默认没有按键时发送此信号
		{
			printf("无");
		}
		if (info->dwPOV == JOY_POVRIGHT)//右
		{
			printf("右");
		}
		if (info->dwPOV == JOY_POVBACKWARD)//后
		{
			printf("后");
		}
		if (info->dwPOV == JOY_POVLEFT)//左
		{
			printf("左");
		}

		Sleep(1000);//程序暂停1秒
	}
}


