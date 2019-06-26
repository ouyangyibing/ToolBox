#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QDebug>
#include <QTimer>
#include <QTcpServer>
#include <QEventLoop>
#include <QMessageBox>
#include <QTcpSocket>
#include "tcpsocket.h"

TcpServer::TcpServer(QWidget *parent) :
    PluginWidget(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);

    setInitUi();

    server = new QTcpServer(this);
    QObject::connect(server, &QTcpServer::newConnection,
                     this, &TcpServer::slotNewSocket);
}

bool TcpServer::listen()
{
    int port = ui->port_spinBox->value();
    return server->listen(QHostAddress::Any, port);
}

void TcpServer::setInitUi()
{
    isListen = false;
    ui->listen_btn->setText("监听");
    ui->port_spinBox->setDisabled(false);
}

void TcpServer::closeSocket()
{
    server->close();
}

void TcpServer::setListenPortUi()
{
    isListen = true;
    ui->listen_btn->setText("关闭");
    ui->port_spinBox->setDisabled(true);
}

TcpServer::~TcpServer()
{
    delete ui;
}

TcpServer *TcpServer::newObj()
{
    static bool flag = false;

    if(flag) {
        return new TcpServer();

    } else {
        flag = true;
        return this;
    }
}

void TcpServer::slotNewSocket()
{
    while (server->hasPendingConnections()) {
        TcpSocket *socket = new TcpSocket(this);
        socket->setSocket( server->nextPendingConnection());
    }
}

void TcpServer::on_listen_btn_clicked()
{
    if(!isListen) {
        if(!listen()) {
            QMessageBox::warning(this, "警告", "监听失败！");
            return ;
        }
        setListenPortUi();

    } else {
        closeSocket();
        setInitUi();
    }
}
