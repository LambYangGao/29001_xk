#pragma once

class __declspec(dllexport) MyCordTrans
{
public:
    MyCordTrans(void);
    ~MyCordTrans(void);

public:
	//函数功能，输入设备的经纬高、设备的飞行姿态、目标的距离、方位、俯仰，计算得出目标的经纬高
	//
	//输入参数：self_lat设备自身纬度,self_log设备自身经度,self_h设备自身高度
	//输入参数：yaw设备自身偏北角，自北顺时针偏角为正,pitch设备纵摇角，机头向上为正,roll设备横滚角，飞机右边翅膀向下的角度为正
	//输入参数：目标极坐标：dist_target目标距离，单位米, azimuth_target目标方位角, pitch_target目标俯仰角
	//输出参数：计算返回的经纬高：target_lat纬度, target_log经度, target_h高度（米）
    void targetPolar2TargetGps(double self_lat, double self_log, double self_h,
        double yaw, double pitch, double roll,
        double dist_target, double azimuth_target, double pitch_target,
        double& target_lat, double& target_log, double& target_h
    );
	//函数功能，输入设备的经纬高、设备的飞行姿态、目标的经纬高，计算得出目标的距离、方位、俯仰
	//
	//输入参数：self_lat设备自身纬度,self_log设备自身经度,self_h设备自身高度
	//输入参数：目标经纬高：target_lat纬度, , target_log经度, target_h高度（米）
	//输入参数：yaw设备自身偏北角，自北顺时针偏角为正,pitch设备纵摇角，机头向上为正,roll设备横滚角，飞机右边翅膀向下的角度为正
	//输出参数：计算返回的目标极坐标：dist_target目标距离，单位米, azimuth_target目标方位角, pitch_target目标俯仰角
    void targetGps2TargetPolar(double self_lat, double self_log, double self_h,
        double target_lat, double target_log, double target_h,
        double yaw, double pitch, double roll,
        double& dist_target, double& azimuth_target, double& pitch_target
    );
    //计算两经纬高间的距离
	//
	//输入参数：经纬高1：lat1纬度, log1经度, h1高度
	//输入参数：经纬高2：lat2纬度, log2经度, h2高度
	//返回两经纬高间的距离：distance，单位米   
    double gps2GpsDis(double lat1, double log1, double h1,
        double lat2, double log2, double h2
    );
};
