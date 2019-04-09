#include "udp.h"
#include <QDebug>
#include "ui_udp.h"
#include "myassistant.h"
#include <QUdpSocket>
#include <QMessageBox>

UDP::UDP(QWidget *parent) :
    PluginWidget(parent),
    ui(new Ui::UDP)
{
    ui->setupUi(this);

    socket = new QUdpSocket(this);
    connect(socket, &QUdpSocket::readyRead, this, &UDP::slot_readyRead);
}

void UDP::on_bind_clicked()
{
    if(isBind) {
        if(!openSocket()) {
            QMessageBox::warning(this, "警告", "开启监听失败！");
            return ;
        }
        isBind = false;
        ui->bind->setText("关闭");

    } else {
        closeSocket();
        isBind = true;
        ui->bind->setText("监听");
    }
}

void UDP::slot_readyRead()
{
    qDebug()<< "ready read";
    QByteArray datagram;

    while (socket->hasPendingDatagrams()) {
        datagram.resize( socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
        qDebug()<< "read: " << datagram;
    }
    ui->recevieData->append(datagram);
}

bool UDP::openSocket()
{
    quint16 port = ui->cltPort->text().toUInt();
    qDebug()<< "bind port: " << port;
    return socket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
}

void UDP::closeSocket()
{
    socket->close();
}

UDP::~UDP()
{
    delete ui;
}

UDP *UDP::newObj()
{
    static bool flag = false;

    if(flag) {
        return new UDP();

    } else {
        flag = true;
        return this;
    }
}

void UDP::on_send_clicked()
{
    QByteArray sendData = ui->sendData->text().toLocal8Bit();
    QHostAddress address(ui->srvIp->text());
    quint16 port = ui->srvPort->text().toUInt();
    int byte = socket->writeDatagram(sendData, address, port);
    qDebug()<< "send: " << sendData << address << port << byte << endl;
}

void UDP::on_broadcast_clicked()
{
    QByteArray sendData = ui->sendData->text().toLocal8Bit();
    QHostAddress address(ui->srvIp->text());
    quint16 port = ui->srvPort->text().toUInt();
    int byte = socket->writeDatagram(sendData, QHostAddress::Broadcast, port);
    qDebug()<< "send: " << sendData << "Broadcast" << port << byte << endl;
}
