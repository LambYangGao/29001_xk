#include "myserial.h"
#include <QDebug>
#include <QThread>
//#include "wrt_yz.h"
MySerial::MySerial(QObject *parent) 
    : QThread(parent)
    , m_serialport(new QSerialPort())
    , m_timer500(new QTimer)
{
    m_serialport->setReadBufferSize(70);//设置缓冲区大小
    //connect(m_serialport, SIGNAL(readyRead()), this, SLOT(hasPendingDatagram()));
    m_timer500->start(50);
}

void MySerial::run(void)
{
    connect(m_timer500, SIGNAL(timeout()), this, SLOT(hasPendingDatagram()));
}

void MySerial::setInfo(QString portname, qint32 baud = 115200, qint8 parity = 'N', qint8 databits = 8, qint8 stopbits = 1)
{
    m_portname = portname;
    m_baud = baud;
    m_parity = parity;
    m_databits = databits;
    m_stopbits = stopbits;
}

bool MySerial::Close(void)
{
    m_serialport->close();
    return true;
}

bool MySerial::Init(void)
{
    m_serialport->close();
    m_serialport->clear();
    foreach(const QSerialPortInfo & info, QSerialPortInfo::availablePorts())
    {
        if (info.portName() == m_portname)
        {
            isExist = true;
            m_serialport->setPort(info);
            if (m_serialport->open(QIODevice::ReadWrite))
            {
                m_serialport->setFlowControl(QSerialPort::NoFlowControl);

                switch (m_baud)
                {
                case 1200:
                    m_serialport->setBaudRate(QSerialPort::Baud1200);
                    break;
                case 2400:
                    m_serialport->setBaudRate(QSerialPort::Baud2400);
                    break;
                case 4800:
                    m_serialport->setBaudRate(QSerialPort::Baud4800);
                    break;
                case 9600:
                    m_serialport->setBaudRate(QSerialPort::Baud9600);
                    break;
                case 19200:
                    m_serialport->setBaudRate(QSerialPort::Baud19200);
                    break;
                case 38400:
                    m_serialport->setBaudRate(QSerialPort::Baud38400);
                    break;
                case 57600:
                    m_serialport->setBaudRate(QSerialPort::Baud57600);
                    break;
                case 115200:
                    m_serialport->setBaudRate(QSerialPort::Baud115200);
                default:
                    break;
                }

                switch (m_databits)
                {
                case 5:
                    m_serialport->setDataBits(QSerialPort::Data5);
                    break;
                case 6:
                    m_serialport->setDataBits(QSerialPort::Data6);
                    break;
                case 7:
                    m_serialport->setDataBits(QSerialPort::Data7);
                    break;
                case 8:
                    m_serialport->setDataBits(QSerialPort::Data8);
                    break;
                default:
                    break;
                }

                switch (m_parity)
                {
                case 'O':
                    m_serialport->setParity(QSerialPort::OddParity);
                    break;
                case 'E':
                    m_serialport->setParity(QSerialPort::EvenParity);
                    break;
                case 'N':
                    m_serialport->setParity(QSerialPort::NoParity);
                    break;
                default:
                    break;
                }

                switch (m_stopbits)
                {
                case 1:
                    m_serialport->setStopBits(QSerialPort::OneStop);
                    break;
                case 2:
                    m_serialport->setStopBits(QSerialPort::TwoStop);
                    break;
                default:
                    break;
                }
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
    }
    if (!isExist)
    {
        return false;
    }
}

QStringList MySerial::ScanSerialPorts(void)
{
    QStringList seriallist;
    foreach(const QSerialPortInfo & info, QSerialPortInfo::availablePorts())
    {
        seriallist.append(info.portName());
    }
    return seriallist;
}

void MySerial::sendDatagram(const QByteArray &data)
{
    if (isExist)
    {
        m_serialport->write(data);
    }
}
QByteArray getbuffer;

void MySerial::hasPendingDatagram(void)
{
    QByteArray buffer = m_serialport->readAll(); 
    if (buffer.length()>0)
    {
        getbuffer.append(buffer);
        if (getbuffer.length() >= 7)
        {
            emit sig_hasPendingDatagram(getbuffer.left(7));
            getbuffer = getbuffer.right(getbuffer.length() - 7);
        }
    }
}



