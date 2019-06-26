#include "tcpsocket.h"
#include <QTcpSocket>
#include <QHostAddress>

namespace {
static QHash<Ip, TcpSocket *> m_hash;
}

TcpSocket::TcpSocket(QObject *parent) : QObject(parent)
{

}

QTcpSocket *TcpSocket::socket() const
{
    return m_socket;
}

void TcpSocket::setSocket(QTcpSocket *socket)
{
    m_socket = socket;
    connect(m_socket, &QTcpSocket::disconnected, this, &TcpSocket::slotClose);

    ip = m_socket->peerAddress().toString();
    m_hash.insert(ip, this);
}

QHash<Ip, TcpSocket *> &TcpSocket::hash()
{
    return m_hash;
}

void TcpSocket::slotClose()
{
    m_hash.remove(ip);
    emit sigClose();
    deleteLater();
}
