#include "udpsocket.h"
//#include <wrt_xk.h>

UdpSocket::UdpSocket(int port, QObject *parent)
    : ThreadObject(parent)
{
    m_socket = new QUdpSocket(this);
    m_socket->bind(QHostAddress::AnyIPv4,port, QUdpSocket::ShareAddress);
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(hasPendingDatagram()));
}

UdpSocket::~UdpSocket()
{
    delete m_socket;
    m_socket = NULL;
}

void UdpSocket::hasPendingDatagram()
{
    while (m_socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        qint64 length = m_socket->readDatagram(datagram.data(), datagram.size());
        if (length == datagram.size())
        {
            emit sig_hasPendingDatagram(datagram);
        }
    }
}

void UdpSocket::SendDatagram(const QByteArray & data, const QHostAddress& host, const int& port)
{
    if (m_socket != nullptr )
	{
		m_socket->writeDatagram(data, host, port);
    }
}
