#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pluginwidget.h"
#include <QDir>
#include <QHash>
#include <QDebug>
#include <QTimer>
#include <QAction>
#include <QLibrary>
#include <QFileInfo>
#include <QEventLoop>
#include <QJsonObject>
#include <QPluginLoader>

QHash<QString, QString> pluginPath;
QHash<PluginWidget*, QPluginLoader*> plugins;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDir pluginDir(qApp->applicationDirPath());
    pluginDir.cd("plugins");

    for(QFileInfo info : pluginDir.entryInfoList(QStringList("*.dll"), QDir::Files)) {

        if (!QLibrary::isLibrary(info.absoluteFilePath()))
            continue;

        QPluginLoader loader(info.absoluteFilePath());
        QJsonObject json = loader.metaData().value("MetaData").toObject();
        QString name = json.value("name").toString();
        QAction *action = new QAction(name, ui->mainToolBar);
        action->setObjectName(name);
        ui->mainToolBar->addAction(action);
        connect(action, &QAction::triggered, this, &MainWindow::slot_newInstance);

        pluginPath.insert(name, info.absoluteFilePath());
        loader.unload();
    }
}

MainWindow::~MainWindow()
{
    for(auto unloade : plugins) {
        qDebug()<< unloade->unload();
    }

    delete ui;
}

void MainWindow::slot_newInstance()
{
    QAction *action = qobject_cast<QAction*>(sender());

    auto path = pluginPath.value(action->objectName());
    auto *loader = new QPluginLoader(path);

    PluginWidget *plugin = qobject_cast<PluginWidget *>(loader->instance());
    if(Q_NULLPTR == plugin) {
        qDebug()<< "error: " << action->objectName();
        return ;
    }
    plugin = plugin->newObj();
    ui->mdiArea->addSubWindow(plugin);
    plugin->show();
    plugins.insert(plugin, loader);
}
