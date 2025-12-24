#include "GimbalController.h"
#include <cstring> 

GimbalController::GimbalController(QObject* parent)
    : QObject(parent)
{
}

void GimbalController::startMove(int speedAz, int speedEl)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_MOVE;
    msg.param_1 = speedAz;
    msg.param_2 = speedEl;
    emit requestSendFk(msg);
}

void GimbalController::stopMove()
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_STOP; // 有些协议需要先发 MOVE 0 0 再发 STOP，视具体情况，这里还原原代码逻辑
    // 原代码在 stop 时发送了两次指令：先 MOVE(0,0) 后 STOP。
    // 为了保持一致性，我们可以发一个信号序列，或者调用 startMove(0,0) 然后再发 STOP
    // 这里简化处理，直接发 STOP，如果需要 MOVE(0,0) 可由 UI 层组合或在此处连续 emit

    // 还原原代码逻辑：先停转
    XKDownMsg msgStopMove;
    std::memset(&msgStopMove, 0, sizeof(XKDownMsg));
    msgStopMove.msg_type = E_FK_SF_MOVE;
    msgStopMove.param_1 = 0;
    msgStopMove.param_2 = 0;
    emit requestSendFk(msgStopMove);

    // 再刹车
    msg.msg_type = E_FK_SF_STOP;
    emit requestSendFk(msg);

    // 原代码最后还有一个 E_FK_BUTT，通常是无效指令用于占位，这里忽略
}

void GimbalController::moveToAbsolute(int azCode, int elCode)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_MOVE_TO;
    msg.param_1 = azCode;
    msg.param_2 = elCode;
    emit requestSendFk(msg);
}

void GimbalController::moveRelative(int deltaAzCode, int deltaElCode)
{
    // 相对移动在底层协议中通常表现为“移动多少度”或者“移动到 当前+delta”
    // 根据原代码逻辑，点击移动使用的是 E_FK_SF_MOVE_TO 参数为增量(param_1 = diff_x) ???
    // 仔细看原代码 OnScreenClick_VL_left:
    // m_xk_down_msg.param_1 = diff_x; ... msg_type = E_FK_SF_MOVE_TO;
    // 看来这个协议的 MOVE_TO 如果参数较小可能是增量，或者原代码逻辑有特殊定义。
    // 我们完全还原原代码的行为：
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_MOVE_TO;
    msg.param_1 = deltaAzCode;
    msg.param_2 = deltaElCode;
    emit requestSendFk(msg);
}

void GimbalController::goToPreset(int presetIndex)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_YZW_TO;
    msg.param_1 = presetIndex;
    emit requestSendFk(msg);
}

void GimbalController::setPreset(int presetIndex, int currentAzCode, int currentElCode)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_YZW_INSERT;
    msg.param_1 = presetIndex;
    msg.param_2 = currentAzCode;
    msg.param_3 = currentElCode;
    emit requestSendFk(msg);
}

void GimbalController::deletePreset(int presetIndex)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_YZW_DALETE;
    msg.param_1 = presetIndex;
    emit requestSendFk(msg);
}

void GimbalController::restoreZero()
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_RESTORE;
    emit requestSendFk(msg);
}

void GimbalController::stow()
{
    // 收藏位置: Az 0, El -50 (原代码逻辑)
    moveToAbsolute(0, -50 * 1000);
}

void GimbalController::startSectorScan(int centerAzCode, int rangeCode)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_FWAUTO;
    msg.param_1 = centerAzCode;
    msg.param_2 = rangeCode;
    emit requestSendFk(msg);
}

void GimbalController::startCircleScan()
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_ZHOUSAO;
    emit requestSendFk(msg);
}

void GimbalController::setScanParams(int speed, int elTop, int elBottom, int elStep)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_SAOMIAO_INFO;
    msg.param_1 = speed;
    msg.param_2 = elTop;
    msg.param_3 = elBottom;
    msg.param_4 = elStep;
    emit requestSendFk(msg);
}

void GimbalController::calibrateAzimuth(int mode)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_BIAOJIAO_X;
    msg.param_1 = mode;
    emit requestSendFk(msg);
}

void GimbalController::calibrateElevation(int mode)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_BIAOJIAO_Y;
    msg.param_1 = mode;
    emit requestSendFk(msg);
}

void GimbalController::calibrateAny(int azCode, int elCode)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_BIAOJIAO_ANY;
    msg.param_1 = 1; // enable

    // 原代码的数据清洗逻辑
    if (azCode < 0) azCode += 360000;
    if (elCode < 0) elCode += 360000;

    msg.param_2 = azCode;
    msg.param_3 = elCode;
    emit requestSendFk(msg);
}

void GimbalController::setElevationLimit(int elMax, int elMin)
{
    XKDownMsg msg;
    std::memset(&msg, 0, sizeof(XKDownMsg));
    msg.msg_type = E_FK_SF_FY_BIANJIE;
    msg.param_1 = elMax;
    msg.param_2 = elMin;
    emit requestSendFk(msg);
}

// --- Static Helpers ---

float GimbalController::degToRad(float deg)
{
    return deg * (M_PI / 180.0);
}

float GimbalController::radToDeg(float rad)
{
    return rad * (180.0 / M_PI);
}

void GimbalController::calculateDeltaAngles(
    double u_d, double v_d,
    double W_d, double H_d,
    double W, double H,
    double fov_h, double fov_v,
    double theta_0, double phi_0,
    double& deltaTheta, double& deltaPhi
) {
    // 将显示框坐标转换为图像坐标
    double u = (u_d / W_d) * W;
    double v = (v_d / H_d) * H;

    // 计算点击位置相对于图像中心的偏移量
    double delta_u = u - W / 2;
    double delta_v = v - H / 2;

    // 将视场角从度转换为弧度
    double fov_h_rad = degToRad(fov_h);
    double fov_v_rad = degToRad(fov_v);

    // 归一化处理
    double norm_u = delta_u / (W / 2);
    double norm_v = delta_v / (H / 2);

    // 计算点击位置的方向角度（透视投影修正）
    double theta_click = atan2(norm_u, 1 / tan(fov_h_rad / 2));
    double phi_click = -atan2(norm_v, 1 / tan(fov_v_rad / 2));

    // 计算增量 (弧度转度)
    deltaTheta = radToDeg(theta_click);
    deltaPhi = radToDeg(phi_click);
}