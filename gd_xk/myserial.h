#ifndef MYSERIAL_H
#define MYSERIAL_H

#include <QObject>
#include <QSerialPortInfo>
#include <QSerialPort>
#include "threadobject.h"
#include <QTimer>
class MySerial : public QThread
{
    Q_OBJECT
public:
    explicit MySerial(QObject *parent = nullptr);
    virtual void run(void) override;
    QSerialPort* GetThisSerial(void){return m_serialport;}
    QStringList ScanSerialPorts(void);
    void setInfo(QString portname, qint32 baud, qint8 parity, qint8 databits, qint8 stopbits);
    bool Init(void);
    bool Close(void);
    bool isExist = false;

signals:
    void sig_hasPendingDatagram(QByteArray data);
public slots:
    void sendDatagram(const QByteArray& data);
private slots:
    void hasPendingDatagram(void);
private:
    QSerialPort* m_serialport;//串口对象
    QTimer* m_timer500;
    QString m_portname;//设备名
    qint32 m_baud = 115200;//波特率
    qint8 m_databits = 8;//数据位
    qint8 m_flowcontrol;//流控制
    qint8 m_stopbits;//停止位
    qint8 m_parity;//校验方式
};

#endif // MYSERIAL_H
