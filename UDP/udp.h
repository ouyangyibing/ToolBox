#ifndef UDP_H
#define UDP_H

#include <QWidget>
#include "pluginwidget.h"

class QUdpSocket;

namespace Ui {
class UDP;
}

class UDP : public PluginWidget
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginWidget_iid FILE "UDP.json")
    Q_INTERFACES(PluginWidget)

public:
    explicit UDP(QWidget *parent = 0);
    ~UDP();

    virtual UDP *newObj() Q_DECL_OVERRIDE;

private slots:
    void on_bind_clicked();
    void slot_readyRead();

    void on_send_clicked();

    void on_broadcast_clicked();

private:
    Ui::UDP *ui;

    QUdpSocket *socket;

    bool isBind = true;

    bool openSocket();
    void closeSocket();
};

#endif // UDP_H