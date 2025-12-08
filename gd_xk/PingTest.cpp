#include "PingTest.h"
#include <QProcess>

PingTest::PingTest(QString ip, QObject *parent)
	: QThread(parent)
{
    m_ip = ip;
}

PingTest::~PingTest(void)
{}

void PingTest::run(void)
{
    while (true)
    {
        //与指控连接状态
        bool b_fk_constate = pingTest(m_ip);
        
        emit sig_pingResult(b_fk_constate);

        sleep(20);
    }
}

bool PingTest::pingTest(QString ip)
{
    QProcess pingProcess;
    QString strArg = "ping " + ip + " -n 1 -i 2";
    pingProcess.start(strArg, QIODevice::ReadOnly);
    pingProcess.waitForFinished(-1);
    QString p_sydout = QString::fromLocal8Bit(pingProcess.readAllStandardOutput());
    bool bPingSuccess = false;
    if (p_sydout.contains("TTL="))
    {
        bPingSuccess = true;
    }
    else
    {
        bPingSuccess = false;
    }
    return bPingSuccess;
}
