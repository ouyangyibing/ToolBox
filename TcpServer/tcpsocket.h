#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>

class QTcpSocket;
using Ip = QString;

class TcpSocket : public QObject
{
    Q_OBJECT

public:
    explicit TcpSocket(QObject *parent = nullptr);

    QTcpSocket *socket() const;
    void setSocket(QTcpSocket *socket);

    static QHash<Ip, TcpSocket *> &hash();

signals:
    void sigClose();

public slots:
    void slotClose();

private:
    Ip ip;
    QTcpSocket *m_socket;
};

#endif // TCPSOCKET_H
