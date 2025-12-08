#pragma once

#include "database88002lib_global.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDateTime>
#include <mutex>
#include <stdio.h>
#include <vector>

class DATABASE88002_EXPORT Database88002
{
public:

    struct targetInfo
    {
        QDateTime time;
        QString category;
        float horizontal;
        float vertical;
    };

    struct sysFaultInfo
    {
        QDateTime time;
        QString ir;
        QString vl;
        QString laserDet;
        QString sd;
    };

    struct sysUserInfo
    {
        QDateTime time;
        QString userName;
        QString password;
        int type;

    };


    Database88002();
    ~Database88002(void);
    //时间 QDateTime time,目标种类 category,方位角 horizontal,俯仰角 vertical
    bool insertTargets(QDateTime time, QString category, float horizontal, float vertical);
    bool queryTargets(QDateTime beginTime, QDateTime endTime, std::vector<targetInfo>& targets);
    bool modifyTargets(QDateTime time, QString category_from, QString category_to,
                                       float horizontal_from, float horizontal_to,
                                       float vertical_from, float vertical_to);
    bool clearTargets(QDateTime beginTime, QDateTime endTime);
    bool clearTargets(QDateTime time, QString category, float horizontal, float vertical);
    //时间 QDateTime time,红外状态 ir,可见光状态 vl,激光测距状态 laserDet,伺服状态 sd
    bool insertSysfault(QDateTime time, QString ir, QString vl, QString laserDet, QString sd);
    bool querySysfault(QDateTime beginTime, QDateTime endTime, std::vector<sysFaultInfo>& sysFaults);
    bool modifySysfault(QDateTime time, QString ir_from, QString ir_to, QString vl_from, QString vl_to,
                                        QString laserDet_from, QString laserDet_to,
                                        QString sd_from, QString sd_to);
    bool clearSysfault(QDateTime beginTime, QDateTime endTime);
    bool clearSysfault(QDateTime time, QString ir, QString vl, QString laserDet, QString sd);
    //时间 QDateTime time,用户名 userName,密码 password,用户类型 type
    bool insertSysUser(QDateTime time, QString userName, QString password, int type);
    bool querySysUser(QDateTime beginTime, QDateTime endTime, std::vector<sysUserInfo>& sysUserInfos);
    bool modifySysUser(QDateTime time, QString userName_from, QString userName_to, 
                                       QString password_from, QString password_to,
                                       int type_from,int type_to);
    bool clearSysUser(QString userName);
    bool clearSysUser(QDateTime time, QString userName);
    //
    void databaseClose();
private:
    QSqlDatabase m_DataBase;
    QSqlQuery m_Query;
    std::mutex m_lock;

};
