#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QUdpSocket>
#include "threadobject.h"

class UdpSocket : public ThreadObject
{
    Q_OBJECT
public:
    explicit UdpSocket(int port, QObject *parent = nullptr);
    ~UdpSocket();

    QUdpSocket* m_socket;
signals:
    //接收数据需要将这个信号绑定到数据接收的槽
    void sig_hasPendingDatagram(QByteArray data);
public slots:
    //发送数据时 发送信号到这个槽
    void SendDatagram(const QByteArray & data, const QHostAddress& host, const int& port);
private slots:
    void hasPendingDatagram();
private:
};

#endif // UDPSOCKET_H
