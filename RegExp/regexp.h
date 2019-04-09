#ifndef REGEXP_H
#define REGEXP_H

#include <QWidget>
#include "pluginwidget.h"

namespace Ui {
class RegExp;
}

class RegExp : public PluginWidget
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PluginWidget_iid FILE "RegExp.json")
    Q_INTERFACES(PluginWidget)

public:
    explicit RegExp(QWidget *parent = 0);
    ~RegExp();

    virtual RegExp *newObj() Q_DECL_OVERRIDE;

private slots:
    void slot_regExp();
    void on_openFile_clicked();

private:
    Ui::RegExp *ui;
};

#endif // REGEXP_H
