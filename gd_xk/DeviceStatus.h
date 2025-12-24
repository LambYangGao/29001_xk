#pragma once
#include <QObject>
#include <QMetaType>

// 使用 Q_GADGET 支持元对象系统，不需要继承 QObject 的重量级特性，但支持反射和信号槽传递
class DeviceStatus {
    Q_GADGET
public:
    // 伺服模式枚举 (映射原协议中的 mode 值)
    enum class ServoMode {
        Unknown = 0,
        FanScan = 1,      // 扇扫
        CircleScan = 2,   // 周扫
        Follow = 4,       // 随动
        Tracking = 8,     // 跟踪
        Collection = 16,  // 收藏
        Zeroing = 32,     // 归零
        Stop = 64,        // 停止
        SemiAuto = 128    // 半自动
    };
    Q_ENUM(ServoMode)

        // 目标类型枚举 (映射原协议中的 target type)
        enum class TargetType {
        Unknown = 0,
        RotorDrone = 1,     // 旋翼无人机
        FixedWingDrone = 2, // 固定翼无人机
        Helicopter = 3,     // 直升机
        Balloon = 4,        // 空飘物(气球)
        HotAirBalloon = 5,  // 空飘物(热气球)
        Airliner = 6,       // 民航
        Car = 7,            // 车
        Bird = 8,           // 鸟
        LargeDrone = 9      // 大型无人机
    };
    Q_ENUM(TargetType)

        // --- 业务属性 (物理量) ---

        // 伺服状态
        ServoMode servoMode = ServoMode::Unknown;
    double azimuth = 0.0; // 方位角 (度)
    double pitch = 0.0;   // 俯仰角 (度)

    // 视场角 (度)
    double vlFovX = 0.0;
    double vlFovY = 0.0;
    double irFovX = 0.0;
    double irFovY = 0.0;

    // 跟踪状态
    bool isTrackingVL = false; // 可见光跟踪中
    bool isTrackingIR = false; // 红外跟踪中

    // 跟踪目标位置 (原始值，用于算法计算或显示)
    int vlTargetRawAz = 0;
    int vlTargetRawEl = 0;
    int irTargetRawAz = 0;
    int irTargetRawEl = 0;

    // 激光测距
    double laserDistance = 0.0; // 目标距离 (米)
    int laserErrorCode = 0;     // 测距错误码 (0 表示正常)

    // 智能识别
    TargetType aiTypeVL = TargetType::Unknown;
    TargetType aiTypeIR = TargetType::Unknown;
    int aiSizeVL = 0;
    int aiSizeIR = 0;

    // 镜头焦距 (处理后的数值)
    int vlFocalLength = 0;
    int irFocalLength = 0;

    // --- 辅助转换函数 ---
    static ServoMode parseServoMode(int mode) {
        // 简单映射，实际可根据需要增加容错
        return static_cast<ServoMode>(mode);
    }
};

Q_DECLARE_METATYPE(DeviceStatus)