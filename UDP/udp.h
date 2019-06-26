#ifndef UDP_H
#define UDP_H

#include <QWidget>
#include <QHostAddress>
#include "pluginwidget.h"

class QUdpSocket;

namespace Ui {
class Udp;
}

class Udp : public PluginWidget
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginWidget_iid FILE "UDP.json")
    Q_INTERFACES(PluginWidget)

public:
    explicit Udp(QWidget *parent = 0);
    ~Udp();

    virtual Udp *newObj() Q_DECL_OVERRIDE;

private slots:
    void on_bind_clicked();
    void slot_readyRead();

    void on_send_clicked();

    void on_broadcast_clicked();

private:
    Ui::Udp *ui;

    QUdpSocket *socket;

    bool isBind = true;
    QHostAddress serverAddress;
    quint16 serverPort;

    bool bindPort();
    void closeSocket();
    void setBindPortUi();
    void setInitUi();
};

#endif // UDP_H
