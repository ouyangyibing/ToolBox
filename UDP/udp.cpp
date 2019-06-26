#include "udp.h"
#include <QDebug>
#include "ui_udp.h"
#include "myassistant.h"
#include <QUdpSocket>
#include <QMessageBox>
#include <QDateTime>

const QString SEND_HEAD = "【发送时间:%1 地址:%2 端口:%3 数据长度:%4】";
const QString RECEIVE_HEAD = "【接收时间:%1 地址:%2 端口:%3 数据长度:%4】";

Udp::Udp(QWidget *parent) :
    PluginWidget(parent),
    ui(new Ui::Udp)
{
    ui->setupUi(this);

    this->setWindowTitle("UDP网络调试助手 v1.0");

    socket = new QUdpSocket(this);
    connect(socket, &QUdpSocket::readyRead, this, &Udp::slot_readyRead);

    setInitUi();
}

void Udp::on_bind_clicked()
{
    if(isBind) {
        closeSocket();
        setInitUi();

    } else {
        if(!bindPort()) {
            QMessageBox::warning(this, "警告", "监听失败！");
            return ;
        }
        setBindPortUi();
    }
}

void Udp::slot_readyRead()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize( socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &serverAddress, &serverPort);

        ui->recevieData->setTextColor(QColor("red"));
        ui->recevieData->append(RECEIVE_HEAD.arg(My::getCurentTime())
                                .arg(serverAddress.toString())
                                .arg(serverPort)
                                .arg(datagram.length()));
        ui->recevieData->append(QString::fromLocal8Bit(datagram));
    }
}

bool Udp::bindPort()
{
    quint16 port = ui->cltPort->text().toUInt();
    return socket->bind(port, QUdpSocket::DontShareAddress);
}

void Udp::closeSocket()
{
    socket->close();
}

void Udp::setInitUi()
{
    isBind = false;
    ui->bind->setText("监听");
    ui->cltPort->setDisabled(false);
    ui->groupBox_send->setDisabled(true);
}

void Udp::setBindPortUi()
{
    isBind = true;
    ui->bind->setText("关闭");
    ui->cltPort->setDisabled(true);
    ui->groupBox_send->setDisabled(false);
}

Udp::~Udp()
{
    delete ui;
}

Udp *Udp::newObj()
{
    static bool flag = false;

    if(flag) {
        return new Udp();

    } else {
        flag = true;
        return this;
    }
}

void Udp::on_send_clicked()
{
    QHostAddress address(ui->srvIp->text());
    quint16 port = ui->srvPort->text().toUInt();
    QByteArray sendData = ui->sendData->toPlainText().toLocal8Bit();
    int length = socket->writeDatagram(sendData, address, port);

    ui->recevieData->setTextColor(QColor("darkgreen"));
    ui->recevieData->append( SEND_HEAD.arg(My::getCurentTime())
                             .arg(address.toString())
                             .arg(port)
                             .arg(length));
    ui->recevieData->append(QString::fromLocal8Bit(sendData));
}

void Udp::on_broadcast_clicked()
{
    quint16 port = ui->srvPort->text().toUInt();
    QByteArray sendData = ui->sendData->toPlainText().toLocal8Bit();
    int length = socket->writeDatagram(sendData, QHostAddress::Broadcast, port);

    ui->recevieData->setTextColor(QColor("darkgreen"));
    ui->recevieData->append(SEND_HEAD.arg(My::getCurentTime())
                            .arg("Broadcast")
                            .arg(port)
                            .arg(length));
    ui->recevieData->append(QString::fromLocal8Bit(sendData));
}
