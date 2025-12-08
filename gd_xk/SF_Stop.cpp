#include "SF_Stop.h"
#include<Windows.h>

SF_Stop::SF_Stop(int time, QObject *parent)
	: QThread(parent)
{
	m_time = time;
}

SF_Stop::~SF_Stop()
{}

void SF_Stop::run()
{
    Sleep(m_time);
	emit sig_timeover();
}
