#ifndef TCP_H
#define TCP_H

#include "pluginwidget.h"
#include <QList>

class QTcpServer;
class TcpSocket;

namespace Ui {
class TcpServer;
}

class TcpServer : public PluginWidget
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginWidget_iid FILE "TcpServer.json")
    Q_INTERFACES(PluginWidget)

public:
    explicit TcpServer(QWidget *parent = 0);
    ~TcpServer();

    virtual TcpServer *newObj() Q_DECL_OVERRIDE;

private slots:
    void slotNewSocket();
    void on_listen_btn_clicked();

private:
    Ui::TcpServer *ui;

    QTcpServer *server;


    bool isListen;
    bool listen();
    void closeSocket();
    void setInitUi();
    void setListenPortUi();

};

#endif // TCP_H
