/**
//json 格式
{
    "name" : "当前插件的名字",
    "version" : "v1.0",
    "dependencies" : [
        { "name" : "被依赖的插件名字", "version" : "被依赖插件的版本" },
        { "name" : "被依赖的插件名字2", "version" : "被依赖插件的版本" }
    ]
}
*/


#ifndef WIDGETPLUGIN_H
#define WIDGETPLUGIN_H

//#include "pluginwidget_global.h"
#include <QWidget>

class PluginWidget : public QWidget
{
    Q_OBJECT
public:
    PluginWidget(QWidget *parent = 0);

    virtual PluginWidget *newObj() = 0;
};

#define PluginWidget_iid "org.qt-project.Qt.Examples.PluginWidget"
Q_DECLARE_INTERFACE(PluginWidget, PluginWidget_iid)

#endif // WIDGETPLUGIN_H
