#pragma once
#include <QObject>
#include <cmath>
#include "protocol_fk.h"
#include "protocol_picxk.h" 


// 定义 M_PI 如果未定义
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class GimbalController : public QObject
{
    Q_OBJECT
public:
    explicit GimbalController(QObject* parent = nullptr);

    // --- 基础运动控制 ---
    // 开始以指定速度运动 (参数通常为 -100 ~ 100 或实际速度值)
    void startMove(int speedAz, int speedEl);

    // 停止运动 (刹车)
    void stopMove();

    // 绝对位置移动 (单位：0.001度，即协议原始单位)
    void moveToAbsolute(int azCode, int elCode);

    // 相对位置移动 (单位：0.001度)
    void moveRelative(int deltaAzCode, int deltaElCode);

    // --- 预置位管理 ---
    void goToPreset(int presetIndex);
    void setPreset(int presetIndex, int currentAzCode, int currentElCode);
    void deletePreset(int presetIndex);

    // --- 高级功能 ---
    void restoreZero(); // 归零
    void stow();        // 收藏

    // 扇扫 (参数单位：0.001度)
    void startSectorScan(int centerAzCode, int rangeCode);

    // 周扫
    void startCircleScan();

    // 扫描参数设置
    void setScanParams(int speed, int elTop, int elBottom, int elStep);

    // --- 校准与限位 ---
    void calibrateAzimuth(int mode = 2); // 方位校准
    void calibrateElevation(int mode = 3); // 俯仰校准
    void calibrateAny(int azCode, int elCode); // 任意点校准
    void setElevationLimit(int elMax, int elMin); // 俯仰限位

    // --- 辅助算法 (静态工具函数) ---
    // 计算屏幕点击对应的角度偏差 (返回度数)
    static void calculateDeltaAngles(
        double u_d, double v_d,     // 鼠标点击坐标
        double W_d, double H_d,     // 播放窗口宽高
        double W, double H,         // 视频分辨率
        double fov_h, double fov_v, // 视场角(度)
        double theta_0, double phi_0, // 当前角度(度) - 实际上此算法算增量，此参数可用于绝对值计算，若只算增量可忽略
        double& deltaTheta, double& deltaPhi // 输出：角度增量(度)
    );

    static float degToRad(float deg);
    static float radToDeg(float rad);

signals:
    // [Dirty Bridge] 请求发送协议数据
    void requestSendFk(const XKDownMsg& msg);
};