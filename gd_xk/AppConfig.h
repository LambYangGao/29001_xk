#pragma once
#include <QObject>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>

class AppConfig : public QObject
{
    Q_OBJECT
public:
    explicit AppConfig(QObject* parent = nullptr) : QObject(parent)
    {
        // 假定配置文件在应用程序同级目录
        QString configPath = QCoreApplication::applicationDirPath() + "/Config.ini";
        m_settings = new QSettings(configPath, QSettings::IniFormat, this);
        // 设置编码，防止中文乱码 (根据实际 ini 编码调整，通常是 UTF-8 或 System)
        m_settings->setIniCodec("UTF-8");
    }

    // --- 预置位管理 (SF_1 ~ SF_50) ---
    QString getPresetName(int index) {
        if (index < 1 || index > 50) return QString();
        return m_settings->value(QString("SF_%1").arg(index), "").toString();
    }

    void setPresetName(int index, const QString& name) {
        if (index < 1 || index > 50) return;
        m_settings->setValue(QString("SF_%1").arg(index), name);
        // QSettings 析构或 sync 时会自动写入，这里无需手动 save
    }

    // --- 激光禁区配置 ---
    struct LaserForbidConfig {
        float fwStart;
        float fwStop;
        float fyStart;
        float fyStop;
    };

    LaserForbidConfig getLaserForbidConfig() {
        LaserForbidConfig cfg;
        cfg.fwStart = m_settings->value("LASER_FORBID_FW_START", 0.0f).toFloat();
        cfg.fwStop = m_settings->value("LASER_FORBID_FW_STOP", 0.0f).toFloat();
        cfg.fyStart = m_settings->value("LASER_FORBID_FY_START", 0.0f).toFloat();
        cfg.fyStop = m_settings->value("LASER_FORBID_FY_STOP", 0.0f).toFloat();
        return cfg;
    }

    void setLaserForbidConfig(const LaserForbidConfig& cfg) {
        m_settings->setValue("LASER_FORBID_FW_START", QString::number(cfg.fwStart));
        m_settings->setValue("LASER_FORBID_FW_STOP", QString::number(cfg.fwStop));
        m_settings->setValue("LASER_FORBID_FY_START", QString::number(cfg.fyStart));
        m_settings->setValue("LASER_FORBID_FY_STOP", QString::number(cfg.fyStop));
    }

    // --- 本机经纬高 ---
    struct LocalLocation {
        double lng;
        double lat;
        double alt;
    };

    LocalLocation getLocalLocation() {
        LocalLocation loc;
        loc.lng = m_settings->value("this_jingdu", 0.0).toDouble();
        loc.lat = m_settings->value("this_weidu", 0.0).toDouble();
        loc.alt = m_settings->value("this_gaodu", 0.0).toDouble();
        return loc;
    }

    void setLocalLocation(const LocalLocation& loc) {
        m_settings->setValue("this_jingdu", QString::number(loc.lng, 'f', 6));
        m_settings->setValue("this_weidu", QString::number(loc.lat, 'f', 6));
        m_settings->setValue("this_gaodu", QString::number(loc.alt, 'f', 2));
    }

    // --- 引导适配参数 ---
    struct GuideAdaptConfig {
        int isAdaptView;
        int pixeVi;
        int pixeIr;
        int viewSize;
    };

    GuideAdaptConfig getGuideAdaptConfig() {
        GuideAdaptConfig cfg;
        cfg.isAdaptView = m_settings->value("IS_GUIDE_ADAPT_VIEW", 0).toInt();
        cfg.pixeVi = m_settings->value("GUIDE_ADPAT_VIEW_PIXE_VI", 0).toInt();
        cfg.pixeIr = m_settings->value("GUIDE_ADPAT_VIEW_PIXE_IR", 0).toInt();
        cfg.viewSize = m_settings->value("GUIDE_ADPAT_VIEW_SIZE", 0).toInt();
        return cfg;
    }

    void setGuideAdaptView(bool enable) {
        m_settings->setValue("IS_GUIDE_ADAPT_VIEW", enable ? "1" : "0");
    }

private:
    QSettings* m_settings;
};