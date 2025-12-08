#pragma once

#include <QThread>

class SF_Stop  : public QThread
{
	Q_OBJECT

public:
	SF_Stop(int time,QObject *parent=nullptr);
	~SF_Stop();

	virtual void run() override;

signals:
	void sig_timeover();

private:
	int m_time = 0;
};
