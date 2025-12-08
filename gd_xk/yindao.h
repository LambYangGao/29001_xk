#pragma once

#include <QObject>

class yindao  : public QObject
{
	Q_OBJECT

public:
	yindao(QObject *parent);
	~yindao();

	void getTargetInfo(double jd, double wd, double gd, double t_jd, double t_wd, double t_gd, double& t_fw, double& t_fy);
	double A2R(double d);
	double R2A(double d);
	double GetDistanceCpp(double lat1, double lng1, double lat2, double lng2);
	double GetYaw(double lat1, double lon1, double lat2, double lon2);
};
