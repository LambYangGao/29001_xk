#include "yindao.h"

yindao::yindao(QObject *parent)
	: QObject(parent)
{}

yindao::~yindao()
{}

void yindao::getTargetInfo(double jd, double wd, double gd, double t_jd, double t_wd, double t_gd, double& t_fw, double& t_fy)
{
    t_fw = GetYaw(wd, jd, t_wd, t_jd);
    double dis = GetDistanceCpp(wd, jd, t_wd, t_jd);
    double hudu = atan2(gd, dis);
    t_fy = R2A(hudu);
    int a = 1;
}

// PI
#define M_PI		3.14159265358979323846

// 地球半径
const double EARTH_RADIUS = 6371000;

// 角度转弧度
double yindao::A2R(double d)
{
    return d * M_PI / 180.0;
}

// 弧度转角度
double yindao::R2A(double d)
{
    return d / M_PI * 180.0;
}

// 获取两经纬度之间的距离(m)
double yindao::GetDistanceCpp(double lat1, double lng1, double lat2, double lng2)
{
    double radLat1 = A2R(lat1);
    double radLat2 = A2R(lat2);
    double a = radLat1 - radLat2;
    double b = A2R(lng1) - A2R(lng2);
    double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2)));
    s = s * EARTH_RADIUS;
    return s;
}

// 获取两经纬度之间的方位角(°) 纬度 精度 纬度 经度
double yindao::GetYaw(double lat1, double lon1, double lat2, double lon2)
{
    double result = 0.0;

    int ilat1 = (int)(0.50 + lat1 * 360000.0);
    int ilat2 = (int)(0.50 + lat2 * 360000.0);
    int ilon1 = (int)(0.50 + lon1 * 360000.0);
    int ilon2 = (int)(0.50 + lon2 * 360000.0);

    lat1 = A2R(lat1);
    lon1 = A2R(lon1);
    lat2 = A2R(lat2);
    lon2 = A2R(lon2);

    if ((ilat1 == ilat2) && (ilon1 == ilon2)) { return result; }
    else if (ilon1 == ilon2) { if (ilat1 > ilat2) { result = 180.0; } }
    else
    {
        double c = acos(sin(lat2) * sin(lat1) + cos(lat2) * cos(lat1) * cos((lon2 - lon1)));
        double A = asin(cos(lat2) * sin((lon2 - lon1)) / sin(c));

        result = R2A(A);

        if ((ilat2 > ilat1) && (ilon2 > ilon1)) {}
        else if ((ilat2 < ilat1) && (ilon2 < ilon1)) { result = 180.0 - result; }
        else if ((ilat2 < ilat1) && (ilon2 > ilon1)) { result = 180.0 - result; }
        else if ((ilat2 > ilat1) && (ilon2 < ilon1)) { result += 360.0; }
    }

    if (result < 0) { result += 360.0; }
    if (result > 360) { result -= 360.0; }

    return result;
}
