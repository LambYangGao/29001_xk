#pragma once

#include <QThread>

class PingTest  : public QThread
{
	Q_OBJECT

public:
	PingTest(QString ip,QObject *parent=nullptr);
	~PingTest();

	virtual void run() override;


	bool pingTest(QString ip);

signals:
	void sig_pingResult(bool res);
private:
	QString m_ip;
};
